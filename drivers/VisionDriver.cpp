#include <vision/core/utilities.hpp>
#include <vision/core/RealsenseInterface.hpp>
#include <common/messages/depth_image_t.hpp>
#include <common/messages/rgb_image_t.hpp>

#include <opencv2/core.hpp>
#include <zcm/zcm-cpp.hpp>
#include <yaml-cpp/yaml.h>
#include <opencv2/imgproc/imgproc.hpp>

#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <thread>
#include <mutex>
#include <atomic>
#include <condition_variable>
#include <csignal>
#include <functional>

using std::cout;
using std::endl;
using std::cerr;
using std::string;
using std::vector;
using std::shared_ptr;
using std::thread;
using std::mutex;
using std::unique_lock;
using std::condition_variable;
using std::atomic_bool;
using std::function;

using zcm::ZCM;

using cv::Mat;

using vision::CameraPoseData;
using vision::RealsenseInterface;

// Start CameraWrapper Section **************************************

class CameraWrapper
{
public:
    CameraWrapper(const YAML::Node& config, shared_ptr<ZCM> zcm_ptr);
    void start();
    void stop();
    void join();
    void init_tasks(); // Set starting task metadata
    static void run_camera(CameraWrapper* self);
    static void broadcast_rgbd(const Mat rgb, const Mat depth, int64_t utime, CameraWrapper* self);
private:
    RealsenseInterface interface_;
    shared_ptr<ZCM> zcm_ptr_;
    atomic_bool stay_alive_;
    bool enabled_;
    thread camera_thread_;
    // Task metadata section (managed)
    atomic_bool broadcast_rgbd_running_;
};

CameraWrapper::CameraWrapper(const YAML::Node& config, shared_ptr<ZCM> zcm_ptr) :
    interface_ {RealsenseInterface(config)}, zcm_ptr_ {zcm_ptr}, stay_alive_ {atomic_bool(true)},
    enabled_ {config["enabled"].as<bool>()}
{
}

void CameraWrapper::start()
{
    if (!enabled_) return;
    camera_thread_ = thread(run_camera, this);
}

void CameraWrapper::stop()
{
    stay_alive_ = false;
}

void CameraWrapper::join()
{
    if (enabled_) camera_thread_.join();
}

void CameraWrapper::init_tasks()
{
    broadcast_rgbd_running_ = false;
}

void CameraWrapper::run_camera(CameraWrapper* self)
{
    // Disable the autoexposure, is here because this has sleeps in it
    // It is better to be done asynchronyously, else it would be in the constructor
    self->interface_.disableAutoExposure();
    self->init_tasks();
    // Read frames and spawn off handlers
    while (self->stay_alive_)
    {
        // Load the next frame, if no new frame then skip iteration
        if (!self->interface_.loadNext()) continue;
        // Grab everything needed for tasks
        cv::Mat rgb = self->interface_.getRGB();
        cv::Mat depth = self->interface_.getDepth();
        int64_t utime = self->interface_.getUTime();
        // Start up task threads (task threads handle lifetime on their own using task metadata)
        thread(CameraWrapper::broadcast_rgbd, rgb, depth, utime, self).detach();
    }
}

// Task threads of CameraWrapper implementations

void CameraWrapper::broadcast_rgbd(const Mat rgb, const Mat depth, int64_t utime, 
    CameraWrapper* self)
{
    // Set metadata at start
    if (self->broadcast_rgbd_running_)
    {
        cerr << "broadcast_rgbd took too long!\n";
    }
    self->broadcast_rgbd_running_ = true;

    rgbd_image_t rgbd;

    rgbd.rgb_image.width = rgb.cols;
    rgbd.rgb_image.height = rgb.rows;
    rgbd.rgb_image.size = rgbd.rgb_image.width * rgbd.rgb_image.height * 3;
    const int8_t* raw_color = reinterpret_cast<const int8_t*>(rgb.data);
    rgbd.rgb_image.raw_image.assign(raw_color, raw_color + rgbd.rgb_image.size);

    rgbd.depth_image.width = depth.cols;
    rgbd.depth_image.height = depth.rows;
    rgbd.depth_image.size = rgbd.depth_image.width * rgbd.depth_image.height;
    const int16_t* raw_depth = reinterpret_cast<const int16_t*>(depth.data);
    rgbd.depth_image.raw_image.assign(raw_depth, raw_depth + rgbd.depth_image.size);

    rgbd.utime = utime;

    // TODO Channel names should be stored in a config file
    // CameraWrapper should get channel name from this config file
    self->zcm_ptr_->publish("TODO_CHANNEL_NAMES", &rgbd);

    self->broadcast_rgbd_running_ = false;
}
// End task threads of CameraWrapper implementations
// End CameraWrapper Section **************************************

// Set up graceful exit code
function<void(int)> sigHandlerImpl;
void sigHandler(int sig) {sigHandlerImpl(sig);}

int main(int argc, char**argv)
{
    string config_file_path = "../config/camera-config.yaml";
    // Parse program options and get config file
    char opt;
    while ((opt = getopt(argc,argv,"abc:d")) != EOF)
    {
        switch(opt)
        {
            case 'c': 
                config_file_path = string(optarg);
                break;
            case 'h': 
                cout << "usuage: ./driver -c <config-file-path (none for default)>"
                    << endl;
                break;
            default:
                cout << "unknown option " << opt << endl;
                break;
        }
    }
    YAML::Node config = YAML::LoadFile(config_file_path);
    // Create zcm instance
    shared_ptr<ZCM> zcm_ptr = shared_ptr<ZCM>(new ZCM("udp"));
    // Create camera wrappers
    vector<shared_ptr<CameraWrapper>> wrappers;
    wrappers.reserve(4);
    wrappers.emplace_back(new CameraWrapper(config["forward"], zcm_ptr));
    wrappers.emplace_back(new CameraWrapper(config["downward"], zcm_ptr));
    // Start all the camera wrappers
    for (auto& wrapper : wrappers) wrapper->start();
    // Set up sighandler
    atomic_bool running;
    running = true;
    condition_variable cond_var;
    mutex mtx;
    // Relies upon the global sigHandler above
    sigHandlerImpl = [&] (int)
    {
        unique_lock<mutex> lck(mtx);
        running = false;
        cond_var.notify_one();
    };
    // Must set the sigHandlerImpl before setting signal handling
    signal(SIGINT, sigHandler);
    // signal(SIGABRT, sigHandler);
    // signal(SIGSEGV, sigHandler);
    // signal(SIGTERM, sigHandler);
    // Wait until someone tries to terminate the program
    while (running)
    {
        unique_lock<mutex> lck(mtx);
        cond_var.wait(lck);
    }
    // Stop all the camera wrappers
    for (auto& wrapper : wrappers) wrapper->stop();
    // join all the camera wrappers
    for (auto& wrapper : wrappers) wrapper->join();
}