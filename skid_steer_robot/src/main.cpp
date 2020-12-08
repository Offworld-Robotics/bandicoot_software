#include <ros/ros.h>
#include "../include/motion_controller.hpp"


int main (int argc, char **argv)
{
  ros::init(argc, argv, "motion_controller");
  MotionController node;
  //node.robot_set_goal(0,7,1,"map");
  //bool result = node.robot_execute_single_goal();

  node.robot_set_way_point(6,-4,1,"map");
  node.robot_set_way_point(-4,-4,1,"map");
  node.robot_set_way_point(-7,7,1,"map");
  node.robot_set_way_point(7,7,1,"map");
  node.robot_set_way_point(0,1,1,"map");
  if(node.robot_execute_way_points()){
    ROS_INFO("Reached Goal!");
  }
  ros::spin();
  return 0;
}