cmake_minimum_required(VERSION 3.8)
project(bzzz_core)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(bzzz_msgs REQUIRED)

# Tell the compiler to build the C++ files
add_executable(esp32_bridge src/esp32_bridge_node.cpp)

# Link it to the required ROS 2 libraries
ament_target_dependencies(esp32_bridge rclcpp bzzz_msgs)

# Tell ROS 2 where to install the finished program
install(TARGETS
  esp32_bridge
  DESTINATION lib/${PROJECT_NAME}
)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  # the following line skips the linter which checks for copyrights
  # comment the line when a copyright and license is added to all source files
  set(ament_cmake_copyright_FOUND TRUE)
  # the following line skips cpplint (only works in a git repo)
  # comment the line when this package is in a git repo and when
  # a copyright and license is added to all source files
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()
