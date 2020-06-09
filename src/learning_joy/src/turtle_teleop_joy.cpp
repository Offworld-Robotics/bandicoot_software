#include "rclcpp/rclcpp.hpp"
#include "geometry_msgs/msg/twist.hpp"
#include "sensor_msgs/msg/joy.hpp"

using std::placeholders::_1;

class TeleopTurtle : public rclcpp::Node
{
    public:
        TeleopTurtle() : 
            Node("teleop_turtle"),
            linear_(1),
            angular_(2),
            l_scale_(1.0),
            a_scale_(1.0)
        {
            publisher_ = this->create_publisher<geometry_msgs::msg::Twist>(
                    "turtle1/cmd_vel", 10);

            subscription_ = this->create_subscription<sensor_msgs::msg::Joy>(
                    "joy", 10, std::bind(&TeleopTurtle::joyCallback, this, _1));
        }
        
    private:
        int linear_, angular_;
        double l_scale_, a_scale_;

        void joyCallback(const sensor_msgs::msg::Joy::SharedPtr joy);

        rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr publisher_;
        rclcpp::Subscription<sensor_msgs::msg::Joy>::SharedPtr subscription_;
};

void TeleopTurtle::joyCallback(const sensor_msgs::msg::Joy::SharedPtr joy)
{
    geometry_msgs::msg::Twist twist;
    twist.angular.z = a_scale_ * joy->axes[angular_];
    twist.linear.x  = l_scale_ * joy->axes[linear_];
    publisher_->publish(twist);
}

int main(int argc, char *argv[])
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<TeleopTurtle>());
    rclcpp::shutdown();
    return 0;
}

