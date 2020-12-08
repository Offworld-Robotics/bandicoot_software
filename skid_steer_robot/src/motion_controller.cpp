// This code does not work.
// Will be implemented later
// Please refer to /src/simple_motion_controller.cpp for a simple script that demonstates functionality
// Please refer to this write the proper oop motion_controller:
// http://wiki.ros.org/actionlib_tutorials/Tutorials/Writing%20a%20Callback%20Based%20Simple%20Action%20Client

#include "../include/motion_controller.hpp"
#include <cmath>

using namespace std;

void MotionController::robot_set_goal(double x, double y, double w, string frame){
    current_goal.target_pose.header.frame_id = frame;
    current_goal.target_pose.header.stamp = ros::Time::now();

    current_goal.target_pose.pose.position.x = x;
    current_goal.target_pose.pose.position.y = y;
    current_goal.target_pose.pose.position.z =  0.0;
    current_goal.target_pose.pose.orientation.x = 0.0;
    current_goal.target_pose.pose.orientation.y = 0.0;
    current_goal.target_pose.pose.orientation.z = 0.0;
    current_goal.target_pose.pose.orientation.w = w;      
    ROS_INFO("Goal Created!");
}

void MotionController::done_callback(const actionlib::SimpleClientGoalState& state, const move_base_msgs::MoveBaseResultConstPtr& result) 
{
    move_base_msgs::MoveBaseResult r = *result;
    //ROS_INFO("Finished in state [%s]", state.toString().c_str());
    finished_state = state.toString().c_str();
}

void MotionController::active_callback()
{
    //ROS_INFO("Goal just went active");
}

// Called every time feedback is received for the goal
// It generally just sends feedback about its pose etc
void MotionController::feedback_callback(const move_base_msgs::MoveBaseFeedbackConstPtr& feedback)
{

    move_base_msgs::MoveBaseFeedback f = *feedback;

    //http://docs.ros.org/fuerte/api/geometry_msgs/html/msg/Point.html
    geometry_msgs::Point point = f.base_position.pose.position;

    //http://docs.ros.org/fuerte/api/geometry_msgs/html/msg/Quaternion.html
    geometry_msgs::Quaternion quaternion = f.base_position.pose.orientation; 

    //ROS_INFO("Point: \nx: %f, y: %f, z: %f", point.x, point.y, point.z);
    //ROS_INFO("Quaternion:  \n x: %f, y: %f, z: %f, w %f", quaternion.x, quaternion.y, quaternion.z,quaternion.w);

    current_pose.x = point.x;
    current_pose.y = point.y;
    current_pose.w = quaternion.w;
    distance_from_goal = sqrt(pow(current_goal.target_pose.pose.position.x - point.x,2)+ pow(current_goal.target_pose.pose.position.y - point.y,2));

}
bool MotionController::robot_execute_single_goal(){
   // ROS_INFO("Request to Execute Goal sent!");
    return robot_execute_goal(current_goal);
}

bool MotionController::robot_execute_goal(move_base_msgs::MoveBaseGoal goal){
    //ROS_INFO("Sending goal");
    ac.sendGoal(goal,
                boost::bind(&MotionController::done_callback, this, _1, _2),
                boost::bind(&MotionController::active_callback, this),
                boost::bind(&MotionController::feedback_callback, this,_1));
    //ac.sendGoal(goal, &done_callback, &active_callback, &feedback_callback);
    ROS_INFO("To cancel all goals, please publish the following in the terminal \n rostopic pub /move_base/cancel actionlib_msgs/GoalID -- {}");

    while(ac.getState() != actionlib::SimpleClientGoalState::ACTIVE);
    //ROS_INFO("STATE is Active!");

    while(ac.getState() != actionlib::SimpleClientGoalState::SUCCEEDED){
        if(distance_from_goal < 0.3){
            ROS_INFO("Goal Reached!");
            ac.cancelGoal();
            return true;
        }
        if(ac.getState() != actionlib::SimpleClientGoalState::ACTIVE){
            ROS_INFO("Goal Cannot Be Reached!");
            ac.cancelGoal();
            return false;
        }

    }
}

move_base_msgs::MoveBaseGoal MotionController::robot_get_goal(){
    return current_goal;
}

int MotionController::robot_set_way_point(double x, double y, double w, string frame){
    move_base_msgs::MoveBaseGoal newWayPoint;
    newWayPoint.target_pose.header.frame_id = frame;
    newWayPoint.target_pose.header.stamp = ros::Time::now();

    newWayPoint.target_pose.pose.position.x = x;
    newWayPoint.target_pose.pose.position.y = y;
    newWayPoint.target_pose.pose.orientation.w = w;
    wayPoints.push_back(newWayPoint);
    return wayPoints.size();
}

vector<move_base_msgs::MoveBaseGoal> MotionController::robot_get_way_points(){
    return this->wayPoints;
}

void MotionController::robot_remove_way_point(int n){
    wayPoints.erase(wayPoints.begin() + n);
}

bool MotionController::robot_execute_way_points(){
    if( this->wayPoints.empty()) return NULL;
    bool success = false;
    for (auto i = this->wayPoints.begin(); i != this->wayPoints.end(); ++i){
        current_goal = *i;
        current_goal.target_pose.header.stamp = ros::Time::now();
        success = robot_execute_goal(current_goal);
        if (success) {
            ros::Duration(0.5).sleep();
            continue;
        }else {
            if (finished_state == "ABORTED"){
                ROS_INFO("This way point cannot Be Reached, trying next way point.");
                ros::Duration(0.5).sleep();
                continue;
            }
            return success;
        }
    }
    return true;
}

void MotionController::cancel_current_goal(){
    ac.cancelGoal();
}

void MotionController::cancel_all_goals(){
    // TODO Still need to remove all goals from the vector...
    ac.cancelAllGoals();
}