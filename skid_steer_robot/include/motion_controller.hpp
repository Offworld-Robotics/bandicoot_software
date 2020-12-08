// This code does not work.
// Will be implemented later
// Please refer to /src/simple_motion_controller.cpp for a simple script that demonstates functionality
// Please refer to this write the proper oop motion_controller:
// http://wiki.ros.org/actionlib_tutorials/Tutorials/Writing%20a%20Callback%20Based%20Simple%20Action%20Client
#include <ros/ros.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>
#include <vector> 
#include <string>

using namespace std;

typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;

struct pose
{
    float x;
    float y;
    float w;
};


class MotionController
{
    public:
        //functions
        /**
         * @brief The Class constructor. Initialises the MoveBaseClient functionality provided by the actionlib package
         **/
        MotionController() : ac("move_base",true) 
        {
            ROS_INFO("Waiting for action server to start.");
            ac.waitForServer();
            ROS_INFO("Action server started.");
        }

        /**
         * @brief The Destructor.
         **/
        ~MotionController(){};
        
        void done_callback(const actionlib::SimpleClientGoalState& state, const move_base_msgs::MoveBaseResultConstPtr& result);

        // Called once when the goal becomes active
        void active_callback();

        // Called every time feedback is received for the goal
        // It generally just sends feedback about its pose etc
        void feedback_callback(const move_base_msgs::MoveBaseFeedbackConstPtr& feedback);

        /**
         * @brief Sets a single goal. If you want to set multiple goals so that the robot moves to the next goal after it reaches the current goal 
         * @param x The x coordinate of the goal in the specified frame
         * @param y The y coordinate of the goal in the specified frame
         * @param w The angle omega that the robot should come to a rest at when it reaches the goal (x,y) coordinate. Also depends on the specified frame
         * @param frame What frame is the goal being set? The robots frame of the map frame? This will either be something similar to "map" or "base_link" depending on how the map is setup and how the urdf robot frame is set up
         **/
        void robot_set_goal(double x, double y, double w, string frame);
        
        /**
         * @brief Returns the goal set by the robot_set_goal function.
         * @return goal
         **/
        move_base_msgs::MoveBaseGoal robot_get_goal();

        /**
         * @brief Set a way point that robot needs to go to. Multiple way points need to be set if the robot needs to move to several waypoints
         * @param x The x coordinate of the goal in the specified frame
         * @param y The y coordinate of the goal in the specified frame
         * @param w The angle omega that the robot should come to a rest at when it reaches the goal (x,y) coordinate. Also depends on the specified frame
         * @param frame What frame is the goal being set? The robots frame of the map frame? This will either be something similar to "map" or "base_link" depending on how the map is setup and how the urdf robot frame is set up
         * @return Returns the position of the goal paramters provided inside the wayPoints vector for later reference if required
         **/
        int robot_set_way_point(double x, double y, double w, string frame);

        /**
         * @brief Returns the wayPoints vector
         **/
        vector <move_base_msgs::MoveBaseGoal> robot_get_way_points();

        /**
         * @brief Removes a goal within the wayPoints vector according to the int provided
         * @param The goal at position n will be removed from the wayPoints vector
         **/
        void robot_remove_way_point(int n);

        /**
         * @brief Executes the command to move the robot to the specified goal.
         * @param goal The goal position that the robot will move to.
         **/
        bool robot_execute_goal(move_base_msgs::MoveBaseGoal goal);

        /**
         * @brief Moves the robot to goal position stored locally inside this class 
         **/
        bool robot_execute_single_goal();

        /**
         * @brief Moves the robot from one wayPoint to the next based on the goals stores inside the wayPoints vector
         **/
        bool robot_execute_way_points();

        void cancel_current_goal();

        void cancel_all_goals();

    private:
        //Variables
        MoveBaseClient ac;
        move_base_msgs::MoveBaseGoal current_goal;
        struct pose current_pose;
        float distance_from_goal;
        string finished_state;
        vector <move_base_msgs::MoveBaseGoal> wayPoints;
};