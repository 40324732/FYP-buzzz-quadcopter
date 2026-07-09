cmake_minimum_required(VERSION 3.8)
project(bzzz_core)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic -O3)
endif()

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(bzzz_msgs REQUIRED)

find_package(Eigen3 REQUIRED)
include_directories(${EIGEN3_INCLUDE_DIRS})

# Sensors
add_executable(imu_node src/ROS/sensor_nodes/imu_node.cpp)
ament_target_dependencies(imu_node rclcpp sensor_msgs)

add_executable(pressure_node src/ROS/sensor_nodes/pressure_node.cpp)
ament_target_dependencies(pressure_node rclcpp bzzz_msgs)

add_executable(tof_node src/ROS/sensor_nodes/tof_node.cpp)
ament_target_dependencies(tof_node rclcpp bzzz_msgs)

add_executable(anemometer_node src/ROS/sensor_nodes/anemometer_node.cpp)
ament_target_dependencies(anemometer_node rclcpp std_msgs)
target_link_libraries(anemometer_node pthread)

# Flight Controllers
add_executable(altitude_controller_node src/ROS/flight_control_nodes/altitude_controller_node.cpp)
ament_target_dependencies(altitude_controller_node rclcpp sensor_msgs std_msgs bzzz_msgs)

add_executable(attitude_controller_node src/ROS/flight_control_nodes/attitude_controller_node.cpp)
ament_target_dependencies(attitude_controller_node rclcpp sensor_msgs std_msgs bzzz_msgs)

# Utilities
add_executable(rc_node src/ROS/utility_nodes/rc_node.cpp)
ament_target_dependencies(rc_node rclcpp geometry_msgs)

add_executable(data_logger_node src/ROS/utility_nodes/logger_node.cpp)
ament_target_dependencies(data_logger_node rclcpp sensor_msgs geometry_msgs std_msgs bzzz_msgs)

add_executable(esp32_bridge_node src/ROS/utility_nodes/esp32_bridge_node.cpp)
ament_target_dependencies(esp32_bridge_node rclcpp std_msgs bzzz_msgs)

# Install Block
install(TARGETS
  imu_node
  pressure_node
  tof_node
  anemometer_node
  altitude_controller_node
  attitude_controller_node
  rc_node
  data_logger_node
  esp32_bridge_node
  DESTINATION lib/${PROJECT_NAME}
)

ament_package()