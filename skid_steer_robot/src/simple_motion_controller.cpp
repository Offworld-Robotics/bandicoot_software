#include <ros/ros.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>
#include "motion_controller.cpp"

#include "actionlib_msgs/GoalStatus.h"


//http://docs.ros.org/fuerte/api/move_base_msgs/html/msg/MoveBaseAction.html

//Follow this tut to set up a oop class
//http://wiki.ros.org/actionlib_tutorials/Tutorials/Writing%20a%20Callback%20Based%20Simple%20Action%20Client

typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;

move_base_msgs::MoveBaseGoal robot_set_goal(double x, double y, double w, string frame){
    move_base_msgs::MoveBaseGoal goal;

    goal.target_pose.header.frame_id = frame;
    goal.target_pose.header.stamp = ros::Time::now();

    goal.target_pose.pose.position.x = x;
    goal.target_pose.pose.position.y = y;
    goal.target_pose.pose.orientation.w = w;
    ROS_INFO("Goal Created!");
    return goal;
}

// Called once the execution has finished or aborted or etc. 
// The exact state messages that will be sent back are: http://docs.ros.org/api/actionlib_msgs/html/msg/GoalStatus.html
void doneCb(const actionlib::SimpleClientGoalState& state, const move_base_msgs::MoveBaseResultConstPtr& result) {
  
    move_base_msgs::MoveBaseResult r = *result;

    ROS_INFO("Finished in state [%s]", state.toString().c_str());
    

}

// Called once when the goal becomes active
void activeCb()
{
  ROS_INFO("Goal just went active");
}

// Called every time feedback is received for the goal
// It generally just sends feedback about its pose etc
void feedbackCb(const move_base_msgs::MoveBaseFeedbackConstPtr& feedback)
{

    move_base_msgs::MoveBaseFeedback f = *feedback;

    //http://docs.ros.org/fuerte/api/geometry_msgs/html/msg/Point.html
    geometry_msgs::Point point = f.base_position.pose.position;

    //http://docs.ros.org/fuerte/api/geometry_msgs/html/msg/Quaternion.html
    geometry_msgs::Quaternion quaternion = f.base_position.pose.orientation; 

    //ROS_INFO("Point: \nx: %f, y: %f, z: %f", point.x, point.y, point.z);

   // ROS_INFO("Quaternion:  \n x: %f, y: %f, z: %f, w %f", quaternion.x, quaternion.y, quaternion.z,quaternion.w);
}


int main(int argc, char** argv){
  //Setting up the nde here
  ros::init(argc, argv, "navigation");

  //tell the action client that we want to spin a thread by default
  MoveBaseClient ac("move_base", true);

  //wait for the action server to come up
  while(!ac.waitForServer(ros::Duration(5.0))){
      ROS_INFO("Waiting for the move_base action server to come up");
  }

  //Initialising the goal here. 
  //The string here: the 4th argument can either be the "map" or the "link_chassis"
  //The robot will move in the reference of the map frame or the link_chassis frame
  //The word link_chassis -> is actually defined in the robot urdf file. This will not always be the case for all robots.
  //First argument is x, second argument is y, third argument is theta, fourth argument is goal frame -> either "map" or "link_chassi"
  move_base_msgs::MoveBaseGoal goal = robot_set_goal(0,6,1,"map");

  // Sending the goal now, and having three call back functions, all defined above.
  ac.sendGoal(goal, &doneCb, &activeCb, &feedbackCb);

  ROS_INFO("Goal_sent");

  ros::spin();
  return 0;
}