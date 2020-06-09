# Coco software

## Prerequisites

Requires __ROS2 Eloquent__ and the following packages:
*   `ros-eloquent-std-msgs`
*   `ros-eloquent-joy`
*   `ros-eloquent-sensor-msgs`

## Building

1.  Source Eloquent's setup script (usually `/opt/ros/eloquent/setup.bash`).
2.  `colcon build`

## Running

The system is currently split into 2 components: `coco_teleop` and `pwm_control`.

`coco_teleop` is run on the ground-station and forwards joystick data to the robot.

`pwm_control` is run on the robot and translates the joystick data into PWM outputs.

### `coco_teleop`

A launch file is provided that launches the teleoperation and joy(stick) nodes.

`ros2 launch coco_teleop coco_teleop_launch.py`

### `pwm_control`

`ros2 run pwm_control driveCode`

__NOTE:__ Not yet tested, seems to crash silently when not on an rpi.

