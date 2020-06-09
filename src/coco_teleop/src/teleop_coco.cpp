#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/float32.hpp"
#include "sensor_msgs/msg/joy.hpp"

#define AXIS_LEFT  1
#define AXIS_RIGHT 4

using std::placeholders::_1;

class TeleopCoco : public rclcpp::Node
{
    public:
        TeleopCoco() : 
            Node("teleop_coco")
        {
            pub_left_ = this->create_publisher<std_msgs::msg::Float32>(
                    "coco/power_left", 10);
            pub_right_ = this->create_publisher<std_msgs::msg::Float32>(
                    "coco/power_right", 10);

            sub_joy_ = this->create_subscription<sensor_msgs::msg::Joy>(
                    "joy", 10, std::bind(&TeleopCoco::joyCallback, this, _1));
        }
        
    private:
        void joyCallback(const sensor_msgs::msg::Joy::SharedPtr joy);

        rclcpp::Publisher<std_msgs::msg::Float32>::SharedPtr pub_left_;
        rclcpp::Publisher<std_msgs::msg::Float32>::SharedPtr pub_right_;
        rclcpp::Subscription<sensor_msgs::msg::Joy>::SharedPtr sub_joy_;
};

void TeleopCoco::joyCallback(const sensor_msgs::msg::Joy::SharedPtr joy)
{
    std_msgs::msg::Float32 left, right;
    left.data  = joy->axes[AXIS_LEFT];
    right.data = joy->axes[AXIS_RIGHT];

    pub_left_->publish(left);
    pub_right_->publish(right);

    RCLCPP_INFO(this->get_logger(), "Published: left[%f] right[%f].", 
            left.data, right.data);
}

int main(int argc, char *argv[])
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<TeleopCoco>());
    rclcpp::shutdown();
    return 0;
}

