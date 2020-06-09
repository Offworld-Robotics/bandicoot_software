from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
    return LaunchDescription([
        Node(
            package='coco_teleop',
            node_executable='teleop_coco',
        ),
        Node(
            package='joy',
            node_executable='joy_node'
        )
    ])

