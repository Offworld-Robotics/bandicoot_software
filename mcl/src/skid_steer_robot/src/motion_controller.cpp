// This code does not work.
// Will be implemented later
// Please refer to /src/simple_motion_controller.cpp for a simple script that demonstates functionality
// Please refer to this write the proper oop motion_controller:
// http://wiki.ros.org/actionlib_tutorials/Tutorials/Writing%20a%20Callback%20Based%20Simple%20Action%20Client

#include "../include/motion_controller.hpp"

using namespace std;

MotionController::MotionController(){
    //MoveBaseClient ac("move_base", true);
    MoveBaseClient ac_("move_base",true);
    ac = &ac_;
    //wait for the action server to come up
    while(!(ac)->waitForServer(ros::Duration(5.0))){
        ROS_INFO("Waiting for the move_base action server to come up");
    }
    ROS_INFO("Server Setup!");
}

void MotionController::robot_set_goal(double x, double y, double w, string frame){
    goal.target_pose.header.frame_id = frame;
    goal.target_pose.header.stamp = ros::Time::now();

    goal.target_pose.pose.position.x = x;
    goal.target_pose.pose.position.y = y;
    goal.target_pose.pose.orientation.w = w;
    ROS_INFO("Goal Created!");
}


bool MotionController::robot_execute_single_goal(){
    ROS_INFO("Request to Execute Goal sent!");
    return robot_execute_goal(this->goal);
}

bool MotionController::robot_execute_goal(move_base_msgs::MoveBaseGoal g){
    ROS_INFO("Sending goal");
    ac->sendGoal(g);
    ac->waitForResult();
    if(ac->getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
        return true;
    else
        return false;
}

// move_base_msgs::MoveBaseGoal MotionController::robot_get_goal(){
//     return this->goal;
// }

// int MotionController::robot_set_way_point(double x, double y, double w, string frame){
//     move_base_msgs::MoveBaseGoal newWayPoint;
//     newWayPoint.target_pose.header.frame_id = frame;
//     newWayPoint.target_pose.header.stamp = ros::Time::now();

//     newWayPoint.target_pose.pose.position.x = x;
//     newWayPoint.target_pose.pose.position.y = y
//     newWayPoint.target_pose.pose.orientation.w = w;
//     wayPoints.push_back(newWayPoint);
//     return wayPoints-1;
// }

// vector<move_base_msgs::MoveBaseGoal> MotionController::robot_get_way_points(){
//     return this->wayPoints;
// }

// void MotionController::robot_remove_way_point(int n){
//     wayPoints.erase(n);
// }

// bool MotionController::robot_execute_way_points(){
//     if( this->wayPoints == NULL ) return NULL;
//     bool success = false;
//     for (auto i = this->wayPoints.begin(); i != this->wayPoints.end(); ++i)
//         success = robot_execute_single_goal(i);
//         if success 
//             continue;
//         else 
//             return success;
// }