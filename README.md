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
$ sudo apt-get install ros-melodic-slam-gmapping
```

## Installing

Clone this repository in your catkin workspace 'src/' folder.

```sh
$ cd ~/catkin_ws/src/
$ git clone --branch T210_Motion_Control_RHariharan https://github.com/Offworld-Robotics/bandicoot_software.git
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

## Run the Code
You will first launch the world, then spawn the robot inside the world, then you will start the autonomous navigation code.

To launch the world, in a terminal window, type the following
```sh
$ cd ~/catkin_ws
$ roslaunch skid_steer_robot world.launch
```
This will have launched the world inside the skid_steer_robot package.
To launch a world from the provided default gazebo_ros package you can launch another world using any of the following:
```sh
$ roslaunch gazebo_ros willowgarage_world.launch
$ roslaunch gazebo_ros mud_world.launch
$ roslaunch gazebo_ros shapes_world.launch
$ roslaunch gazebo_ros rubble_world.launch
```

In a new terminal, spawn the robot using the 'spawn.launch' file.
```sh
$ cd ~/catkin_ws
$ source devel/setup.bash
$ roslaunch skid_steer_robot spawn.launch
```
Your robot should now have sucessfully spawned inside the world.

In a new terminal, start the autonmous navigation code using the 'navigation.launch' file.
```sh
$ cd ~/catkin_ws
$ source devel/setup.bash
$ roslaunch skid_steer_robot navigation.launch
```
This should have now started pre-configured RVIZ window

### Testing on RVIZ

1. In Rviz, click on the 2D Nav Goal in the top menu. 
2. Click on the Rviz map where you want the robot to navigate too. 

### Testing using bash
In a new terminal, run a program to send a goal position to the robot.
```sh
$ cd ~/catkin_ws
$ source devel/setup.bash
$ rosrun skid_steer_robot goal
```
In the src/simple_motion_controller.cpp file line 82, you will be able to modify the goal position and change the frame etc.

## Trying out AMCL
The amcl + move_base configuration requires that a map be given to it to function properly. At the moment the map of world01 is given to it, and the map itself is store in the map folder.

Launch this world
```sh
$ cd ~/catkin_ws
$ roslaunch skid_steer_robot world.launch
```
In a new terminal, spawn the robot using the 'spawn.launch' file.
```sh
$ cd ~/catkin_ws
$ source devel/setup.bash
$ roslaunch skid_steer_robot spawn.launch
```
Your robot should now have sucessfully spawned inside the world.

In a new terminal, start the amcl code using the 'amcl.launch' file.
```sh
$ cd ~/catkin_ws
$ source devel/setup.bash
$ roslaunch skid_steer_robot amcl.launch
```
This should have now started pre-configured RVIZ window with amcl instead of gmapping

### To create a new map:
1. Launch a world
2. Spawn the robot inside the world
3. In a new terminal, launch "gmapping.launch"
```sh
$ cd ~/catkin_ws
$ source devel/setup.bash
$ roslaunch skid_steer_robot gmapping.launch
```
4. Drive your robot around the world. You may need to install the [teleop-twist-keyboard package](http://wiki.ros.org/teleop_twist_keyboard)
```sh
sudo apt-get install ros-melodic-teleop-twist-keyboard
```
5. Launch the teleop-twist-keyboard code. Instructions on how to control the robot with your keyboard will pop up
```sh
rosrun teleop_twist_keyboard teleop_twist_keyboard.py
```
6. Once you are happy with the map that you have created, you need to save the map:
```sh
rosrun map_server map_saver -f ~/skid_steer_robot/maps/map_name
```
7. In the amcl.launch file, change the map location on line 9 of the code.
8. Now catkin_build, launch your desired world, spawn your robot and start the amcl code!



## Additional: 
### How to point and click on rviz map and output the position
This will be helpful when getting the robot to go to a position on the map, via the simple_motion_controller code to ensure that your position is a valid location!
1. Open a new terminal and type:
```sh
 rostopic echo /clicked_point
```
2. Open Rviz and use Publish a point tool.
3. Click anywhere on the map.
4. The result should be instantaneously displayed in the terminal where we have echoed /clicked_point

### Getting Started on Learning the Theory
Go through the following resources in order and you will understand the basics behind how everything works. A detailed pdf report outlining everything is currently in the works. All of these resources will take a week or two to get through. The first two youtube links are very hands on, and are very highly recommended!

1. [Exploring ROS using a 2 wheeled Robot](https://www.youtube.com/playlist?list=PLK0b4e05LnzY2I4sXWTOA4_82cMh6tL-5)
2. [ROS Navigation in 5 days](https://www.youtube.com/playlist?list=PLiiw0aSVHcAkF26qR6Q7x6RlLAL6-vuF3) 
3. [A website which goes through implementing such a navigation stack from scratch](http://moorerobots.com/blog)
4. [ROS Localisation and Navigation with a Skid-Steer Robot](https://www.haidynmcleod.com/ros-skid-steer-navigation)
5. [move_base tuning guide](http://kaiyuzheng.me/documents/navguide.pdf)

Also be sure to check out the ros wiki for the following!
1. [Gmapping](http://wiki.ros.org/gmapping)
2. [AMCL](http://wiki.ros.org/amcl)
3. [ROS Navigation Stack](http://wiki.ros.org/navigation)


## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.