cmake_minimum_required(VERSION 3.5)
project(learning_joy)

# Default to C++14
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 14)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(geometry_msgs REQUIRED)

add_executable(turtle_teleop_joy src/turtle_teleop_joy.cpp)
ament_target_dependencies(turtle_teleop_joy rclcpp sensor_msgs geometry_msgs)

install(TARGETS
    turtle_teleop_joy
    DESTINATION lib/${PROJECT_NAME})

ament_package()
