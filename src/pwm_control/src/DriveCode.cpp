#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/float64.hpp"
#include <iostream>
#include <string>
#include <pigpio.h>

// define width of pulse
#define NEUTRAL 1500
#define AMPLITUDE_MAX 500

#define PIN_FRONT_LEFT  1
#define PIN_FRONT_RIGHT 2
#define PIN_BACK_LEFT   3
#define PIN_BACK_RIGHT  4

using std::placeholders::_1;

class DriveCode : public rclcpp::Node
{
    public:
        DriveCode() : 
            Node("pwm_node")
        {
            RCLCPP_INFO(this->get_logger(), "Initialising GPIO...");

            // initialise gpio stuff (I think this crashes if not on rpi)
            if (gpioInitialise() < 0) {
                RCLCPP_INFO(this->get_logger(), "Could not initialise GPIO!");
                throw std::runtime_error("could not init GPIO");
            }

            RCLCPP_INFO(this->get_logger(), "GPIO initialised.");
    
            //initialise pin as output
            gpioSetMode(PIN_FRONT_LEFT,  PI_OUTPUT);
            gpioSetMode(PIN_FRONT_RIGHT, PI_OUTPUT);
            gpioSetMode(PIN_BACK_LEFT,   PI_OUTPUT);
            gpioSetMode(PIN_BACK_RIGHT,  PI_OUTPUT);

            RCLCPP_INFO(this->get_logger(), "GPIO pins initialised.");

            //create subscriptions
            sub_frontLeft = this->create_subscription<std_msgs::msg::Float64>(
                    "coco/frontLeft", 10, std::bind(&DriveCode::frontLeftCallback, this, _1));
            sub_frontRight = this->create_subscription<std_msgs::msg::Float64>(
                    "coco/frontRight", 10, std::bind(&DriveCode::frontRightCallback, this, _1));
            sub_backLeft = this->create_subscription<std_msgs::msg::Float64>(
                    "coco/backLeft", 10, std::bind(&DriveCode::backLeftCallback, this, _1));
            sub_backRight = this->create_subscription<std_msgs::msg::Float64>(
                    "coco/backRight", 10, std::bind(&DriveCode::backRightCallback, this, _1));
        }

        ~DriveCode()
        {
            gpioTerminate();
        }

    private:
        void frontLeftCallback(const std_msgs::msg::Float64::SharedPtr scale);
        void frontRightCallback(const std_msgs::msg::Float64::SharedPtr scale);
        void backLeftCallback(const std_msgs::msg::Float64::SharedPtr scale);
        void backRightCallback(const std_msgs::msg::Float64::SharedPtr scale);

        void callback(unsigned pin, double scale);

        rclcpp::Subscription<std_msgs::msg::Float64>::SharedPtr sub_frontLeft;
        rclcpp::Subscription<std_msgs::msg::Float64>::SharedPtr sub_frontRight;
        rclcpp::Subscription<std_msgs::msg::Float64>::SharedPtr sub_backLeft;
        rclcpp::Subscription<std_msgs::msg::Float64>::SharedPtr sub_backRight;
};

void DriveCode::frontLeftCallback(const std_msgs::msg::Float64::SharedPtr scale)
{
    callback(PIN_FRONT_LEFT, scale->data);
}

void DriveCode::frontRightCallback(const std_msgs::msg::Float64::SharedPtr scale)
{
    callback(PIN_FRONT_RIGHT, scale->data);
}

void DriveCode::backLeftCallback(const std_msgs::msg::Float64::SharedPtr scale)
{
    callback(PIN_BACK_LEFT, scale->data);
}

void DriveCode::backRightCallback(const std_msgs::msg::Float64::SharedPtr scale)
{
    callback(PIN_BACK_RIGHT, scale->data);
}

void DriveCode::callback(unsigned pin, double scale)
{
    // Make sure value is inside range -1 to 1        
    if (scale > 1.0) {
        scale = 1.0;
    } else if (scale < -1.0) {
        scale = -1.0;
    }

    // Calculate pulsewidth from scale
    unsigned pulseWidth = NEUTRAL + AMPLITUDE_MAX * scale;

    // Write power value to pin
    gpioServo(pin, pulseWidth);
}

int main(int argc, char *argv[])
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<DriveCode>());
    rclcpp::shutdown();
    return 0;
}
