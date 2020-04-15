# EECS 467 - Autonomous Robotics Final Project
## University of Michigan - Adam Dziedzic, Jingliang Ren, Ryan Wunderly, Jonas Hirshland {dziedada, meow, rywunder, jhirshey}@umich.edu

---

## Goalkeeper

Goalkeeper is an autonomous robot that senses incoming balls and blocks them from passing. It was inspired by goalies in various sports, but mainly soccer. We demonstrate what ability is required in order to react to a human rolling a ball in the robot’s direction.

The arm mimics a human arm playing air hockey, projected to a two-dimensional space. We first used Solidworks to mock up the configuration of Rexarm parts, and then designed a custom end effector and 3D printed the end effector. The arm uses one AX-12+ and two Dynamixel MX-28 servos to move.

## Perception

We use Intel Realsense D435 RGBD cameras for rgb and depth images as well as point clouds of the environment.

---

### Setup and Running

`./scripts/setup.sh`

### Compile the code:

`mkdir build`

`cd build`

`cmake ..`

`make -j`

---
