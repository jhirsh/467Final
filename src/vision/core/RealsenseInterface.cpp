#include <stdlib.h>
#include <chrono>
#include <iostream>
#include <iostream>
#include <thread>

#include "vision/core/RealsenseInterface.hpp"

using cv::Mat;
using std::cout;
using std::endl;
using std::string;

using namespace vision;

RealsenseInterface::RealsenseInterface(YAML::Node config)
    : enabled_(config["enabled"].as<bool>()),
      serial_(config["serial"].as<std::string>()),
      width_(config["width"].as<int>()),
      height_(config["height"].as<int>()),
      fps_(config["fps"].as<int>())
{
    if (!enabled_) return;
    publish_pos_ = config["publish_pose"].as<bool>();
    if (publish_pos_)
    {
        cfg_.enable_stream(RS2_STREAM_POSE, RS2_FORMAT_6DOF);
    }
    else
    {
        cfg_.enable_stream(RS2_STREAM_COLOR, width_, height_, RS2_FORMAT_BGR8, fps_);
        cfg_.enable_stream(RS2_STREAM_DEPTH, width_, height_, RS2_FORMAT_Z16, fps_);
    }
    cfg_.enable_device(serial_);
    rs2::pipeline_profile selection = pipe_.start(cfg_);

    if (!publish_pos_)
    {
        rs2::device selected_dev = selection.get_device();
        rs2::depth_sensor depth_sensor = selected_dev.first<rs2::depth_sensor>();
        depth_sensor.set_option(RS2_OPTION_DEPTH_UNITS, 0.0001);
        // get intrinsics
        auto depth_stream =
            selection.get_stream(RS2_STREAM_DEPTH).as<rs2::video_stream_profile>();
        depth_intrinsics_ = depth_stream.get_intrinsics();

        auto color_stream =
            selection.get_stream(RS2_STREAM_COLOR).as<rs2::video_stream_profile>();
        color_intrinsics_ = color_stream.get_intrinsics();

        // Get the extrinsics
        depth_to_color_ = depth_stream.get_extrinsics_to(color_stream);

        // Get sensors
        sensor_color_ = selection.get_device().query_sensors()[0];
        sensor_depth_ = selection.get_device().query_sensors()[1];

        // Get the scale
        auto sensor = selection.get_device().first<rs2::depth_sensor>();
        scale_ = sensor.get_depth_scale();
        std::cout << "Camera scale: " << scale_ << std::endl;

        // Set up the align object
        // rs2_stream align_to = find_stream_to_align(selection.get_streams());
    }
}

Mat RealsenseInterface::getRGB() const
{
    return Mat(cv::Size(width_, height_), CV_8UC3, (void*)color_image_, Mat::AUTO_STEP).clone();
}

Mat RealsenseInterface::getDepth() const
{
    return Mat(cv::Size(width_, height_), CV_16SC1, (void*)depth_image_, Mat::AUTO_STEP).clone();
}

void RealsenseInterface::disableAutoExposure()
{
    std::this_thread::sleep_for(std::chrono::seconds(2));
    // Auto expose for two seconds
    for (int i = 0; i < 2 * fps_; i++) pipe_.wait_for_frames();

    // Disable
    sensor_color_.set_option(rs2_option::RS2_OPTION_ENABLE_AUTO_EXPOSURE, 0);
    sensor_depth_.set_option(rs2_option::RS2_OPTION_ENABLE_AUTO_EXPOSURE, 0);

    for (int i = 0; i < 2 * fps_; i++) pipe_.wait_for_frames();

    // Enable
    sensor_color_.set_option(rs2_option::RS2_OPTION_ENABLE_AUTO_EXPOSURE, 1);
    sensor_depth_.set_option(rs2_option::RS2_OPTION_ENABLE_AUTO_EXPOSURE, 1);

    // Auto expose for two seconds
    for (int i = 0; i < 2 * fps_; i++) pipe_.wait_for_frames();

    // Disable
    sensor_color_.set_option(rs2_option::RS2_OPTION_ENABLE_AUTO_EXPOSURE, 0);
    sensor_depth_.set_option(rs2_option::RS2_OPTION_ENABLE_AUTO_EXPOSURE, 0);

    std::cout << "Auto exposure disabled." << std::endl;
}

bool RealsenseInterface::loadNext()
{
    if (pipe_.poll_for_frames(&frames_))
    {
        // If publishing pos is tracking camera, therefore, ignore depth
        // and color information and only publish pos info
        if (!publish_pos_)
        {
            unaligned_depth_frame_ = frames_.get_depth_frame();
            unaligned_rgb_frame_ = frames_.get_color_frame();

            // Try to get the frames from processed
            if (unaligned_rgb_frame_)
            {
                color_image_ =
                    static_cast<const uint16_t*>(unaligned_rgb_frame_.get_data());
            }
            if (unaligned_depth_frame_)
            {
                depth_image_ =
                    static_cast<const uint16_t*>(unaligned_depth_frame_.get_data());
            }
        }
        else
        {
            pose_frame_ = frames_.first_or_default(RS2_STREAM_POSE);
        }
        utime_ = std::chrono::duration_cast<std::chrono::microseconds>(
                     std::chrono::system_clock::now().time_since_epoch())
                     .count();
        has_new_cloud_ = false;
        return true;
    }
    return false;
}

RealsenseInterface& RealsenseInterface::operator++()
{
    loadNext();
    return *this;
}

void RealsenseInterface::compute_clouds()
{
    if (has_new_cloud_) return;
    ordered_cloud_ = pcl::PointCloud<pcl::PointXYZ>::Ptr(
        new pcl::PointCloud<pcl::PointXYZ>(width_, height_, pcl::PointXYZ(0, 0, 0)));
    unordered_cloud_ = pcl::PointCloud<pcl::PointXYZ>::Ptr(new pcl::PointCloud<pcl::PointXYZ>());
    for (int dy{0}; dy < depth_intrinsics_.height; ++dy)
    {
        for (int dx{0}; dx < depth_intrinsics_.width; ++dx)
        {
            // Retrieve depth value and map it to more "real" coordinates
            uint16_t depth_value = depth_image_[(dy * depth_intrinsics_.width) + dx];
            float depth_in_meters = depth_value * scale_;
            // Skip over values with a depth of zero (not found depth)
            if (depth_value == 0) continue;
            // For mapping color to depth
            // Map from pixel coordinates in the depth image to pixel
            // coordinates in the color image
            float depth_pixel[2] = {static_cast<float>(dx), static_cast<float>(dy)};
            // Projects the depth value into 3-D space
            float depth_point[3];
            rs2_deproject_pixel_to_point(
                depth_point, &depth_intrinsics_, depth_pixel, depth_in_meters);
            float color_point[3];
            rs2_transform_point_to_point(color_point, &depth_to_color_, depth_point);
            float color_pixel[2]; 
            rs2_project_point_to_pixel(color_pixel, &color_intrinsics_, color_point);
            unordered_cloud_->push_back(pcl::PointXYZ(depth_point[0], 
                depth_point[1], depth_point[2]));
            if (color_pixel[0] < 0 || color_pixel[0] >= width_ || color_pixel[1] < 0 || 
                color_pixel[1] >= height_) continue;
            ordered_cloud_->at(color_pixel[0], color_pixel[1]) = pcl::PointXYZ(depth_point[0], 
                depth_point[1], depth_point[2]);
        }
    }
    has_new_cloud_ = true;
}

pcl::PointCloud<pcl::PointXYZ>::Ptr RealsenseInterface::getPointCloudBasic()
{
    compute_clouds();
    return unordered_cloud_;
}

pcl::PointCloud<pcl::PointXYZ>::Ptr RealsenseInterface::getMappedPointCloud()
{
    compute_clouds();
    return ordered_cloud_;
}

vision::CameraPoseData RealsenseInterface::getPoseData()
{
    CameraPoseData out_pose_data = CameraPoseData();
    auto pose_data = pose_frame_.as<rs2::pose_frame>().get_pose_data();
    // Sets every field of CameraPoseData and returns it
    out_pose_data.x_translation_ = pose_data.translation.x;
    out_pose_data.y_translation_ = pose_data.translation.y;
    out_pose_data.z_translation_ = pose_data.translation.z;

    out_pose_data.x_velocity_ = pose_data.velocity.x;
    out_pose_data.y_velocity_ = pose_data.velocity.y;
    out_pose_data.z_velocity_ = pose_data.velocity.z;

    out_pose_data.x_acceleration_ = pose_data.acceleration.x;
    out_pose_data.y_acceleration_ = pose_data.acceleration.y;
    out_pose_data.z_acceleration_ = pose_data.acceleration.z;

    out_pose_data.Qi_rotation_ = pose_data.rotation.x;
    out_pose_data.Qj_rotation_ = pose_data.rotation.y;
    out_pose_data.Qk_rotation_ = pose_data.rotation.z;
    out_pose_data.Qr_rotation_ = pose_data.rotation.w;

    out_pose_data.x_angular_velocity_ = pose_data.angular_velocity.x;
    out_pose_data.y_angular_velocity_ = pose_data.angular_velocity.y;
    out_pose_data.z_angular_velocity_ = pose_data.angular_velocity.z;

    out_pose_data.x_angular_acceleration_ = pose_data.angular_acceleration.x;
    out_pose_data.y_angular_acceleration_ = pose_data.angular_acceleration.y;
    out_pose_data.z_angular_acceleration_ = pose_data.angular_acceleration.z;

    out_pose_data.tracker_confidence_ = pose_data.tracker_confidence;
    out_pose_data.mapper_confidence_ = pose_data.mapper_confidence;

    return out_pose_data;
}

const void* RealsenseInterface::getRawDepth() const { return depth_image_; }
const void* RealsenseInterface::getRawColor() const { return color_image_; }
int RealsenseInterface::getStreamWidth() const { return width_; }
int RealsenseInterface::getStreamHeight() const { return height_; }
uint64_t RealsenseInterface::getUTime() const { return utime_; }
