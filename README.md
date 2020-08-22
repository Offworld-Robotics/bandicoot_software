# Skid Steer Robot Autonomous Navigation 
This repository contains a  work in progress Robot Operating System (ROS) implementation of an OffWorld Robotics skid-steer robot model for competition with the ROS navigation stack.
The model has functionality to use the Adaptive Monte Carlo Localisation (AMCL) method for localisation with the Elastic band planner method to navigate to goal locations. However, the AMCL with the move_base ros package is quite unreliable due to current configureations and as such the gmapping slam package with move_base is recommended and used here. Launch files for both methods can be found here.

## Prerequisites

1. [Ubuntu](https://www.ubuntu.com/) OS or [debian](https://www.debian.org/distrib/)

2. Robot Operating System (ROS). Installation instructions can be found [here](http://wiki.ros.org/ROS/Installation). Make sureyou install melodic.

3. Install ROS nodes required for the local and global planners, amcl, maps and motor control for the navigation stack.

```sh
$ sudo apt-get update
$ sudo apt-get install ros-melodic-move-base
$ sudo apt-get install ros-melodic-map-server
$ sudo apt-get install ros-melodic-amcl
$ sudo apt-get install ros-melodic-eband-local-planner
$ sudo apt-get install ros-melodic-global-planner
$ sudo apt-get install ros-melodic-teb-local-planner 
$ sudo apt install ros-melodic-moveit
```

## Installing

Clone this repository in your catkin workspace 'src/' folder.

```sh
$ cd ~/catkin_ws/src/
$ git clone --branch T210_Motion_Control_RHariharan https://github.com/Offworld-Robotics/bandicoot_software.git
/bandicoot_software/mcl/src
$ If this does not work, only copy the contents of the /bandicoot_software/mcl/src and copy that into your "~/catkin_ws/src/", otherwise the code will not run.
```

Build the project:
```sh
$ cd ~/catkin_ws
$ catkin_make
```

If you haven’t already, the following line can be added to your .bashrc to auto-source all new terminals
```
source ~/catkin_ws/devel/setup.bash
```