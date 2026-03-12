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

add_executable(imu_node src/imu_node.cpp)
ament_target_dependencies(imu_node rclcpp sensor_msgs)

add_executable(pressure_node src/pressure_node.cpp)
ament_target_dependencies(pressure_node rclcpp bzzz_msgs)

add_executable(tof_node src/tof_node.cpp)
ament_target_dependencies(tof_node rclcpp bzzz_msgs)

add_executable(rc_node src/rc_node.cpp)
ament_target_dependencies(rc_node rclcpp geometry_msgs)

add_executable(anemometer_node src/anemometer_node.cpp)
ament_target_dependencies(anemometer_node rclcpp std_msgs)
target_link_libraries(anemometer_node pthread)

add_executable(flight_controller_node src/flight_controller_node.cpp)
ament_target_dependencies(flight_controller_node 
  rclcpp 
  sensor_msgs 
  std_msgs 
  geometry_msgs 
  bzzz_msgs
)

install(TARGETS
  imu_node
  pressure_node
  tof_node
  rc_node
  anemometer_node
  flight_controller_node
  DESTINATION lib/${PROJECT_NAME}
)

ament_package()