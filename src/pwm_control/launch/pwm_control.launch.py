import launch
import launch.actions
import launch.substitutions
import launch_ros.actions


def generate_launch_description():
    return launch.LaunchDescription([
        launch.actions.DeclareLaunchArgument(
            'node_prefix',
            default_value=[launch.substitutions.EnvironmentVariable('USER'), '_'],
            description='Prefix for node names'),
        launch_ros.actions.Node(
            package='drive_stuff', node_executable='driveCode', output='screen', node_name = "fl_pwm", arguments=["coco/power_left", "2"]),
        launch_ros.actions.Node(
            package='drive_stuff', node_executable='driveCode', output='screen', node_name = "fr_pwm", arguments=["coco/power_left", "4"]),
        launch_ros.actions.Node(
            package='drive_stuff', node_executable='driveCode', output='screen', node_name = "bl_pwm", arguments=["coco/power_right", "6"]),
        launch_ros.actions.Node(
            package='drive_stuff', node_executable='driveCode', output='screen', node_name = "br_pwm", arguments=["coco/power_right", "8"]),
    ])
