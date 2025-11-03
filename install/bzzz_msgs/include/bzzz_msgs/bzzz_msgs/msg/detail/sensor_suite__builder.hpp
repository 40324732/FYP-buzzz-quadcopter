// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from bzzz_msgs:msg/SensorSuite.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "bzzz_msgs/msg/sensor_suite.hpp"


#ifndef BZZZ_MSGS__MSG__DETAIL__SENSOR_SUITE__BUILDER_HPP_
#define BZZZ_MSGS__MSG__DETAIL__SENSOR_SUITE__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "bzzz_msgs/msg/detail/sensor_suite__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace bzzz_msgs
{

namespace msg
{

namespace builder
{

class Init_SensorSuite_baro_pressure
{
public:
  explicit Init_SensorSuite_baro_pressure(::bzzz_msgs::msg::SensorSuite & msg)
  : msg_(msg)
  {}
  ::bzzz_msgs::msg::SensorSuite baro_pressure(::bzzz_msgs::msg::SensorSuite::_baro_pressure_type arg)
  {
    msg_.baro_pressure = std::move(arg);
    return std::move(msg_);
  }

private:
  ::bzzz_msgs::msg::SensorSuite msg_;
};

class Init_SensorSuite_tof_distance
{
public:
  explicit Init_SensorSuite_tof_distance(::bzzz_msgs::msg::SensorSuite & msg)
  : msg_(msg)
  {}
  Init_SensorSuite_baro_pressure tof_distance(::bzzz_msgs::msg::SensorSuite::_tof_distance_type arg)
  {
    msg_.tof_distance = std::move(arg);
    return Init_SensorSuite_baro_pressure(msg_);
  }

private:
  ::bzzz_msgs::msg::SensorSuite msg_;
};

class Init_SensorSuite_gyro_z
{
public:
  explicit Init_SensorSuite_gyro_z(::bzzz_msgs::msg::SensorSuite & msg)
  : msg_(msg)
  {}
  Init_SensorSuite_tof_distance gyro_z(::bzzz_msgs::msg::SensorSuite::_gyro_z_type arg)
  {
    msg_.gyro_z = std::move(arg);
    return Init_SensorSuite_tof_distance(msg_);
  }

private:
  ::bzzz_msgs::msg::SensorSuite msg_;
};

class Init_SensorSuite_gyro_y
{
public:
  explicit Init_SensorSuite_gyro_y(::bzzz_msgs::msg::SensorSuite & msg)
  : msg_(msg)
  {}
  Init_SensorSuite_gyro_z gyro_y(::bzzz_msgs::msg::SensorSuite::_gyro_y_type arg)
  {
    msg_.gyro_y = std::move(arg);
    return Init_SensorSuite_gyro_z(msg_);
  }

private:
  ::bzzz_msgs::msg::SensorSuite msg_;
};

class Init_SensorSuite_gyro_x
{
public:
  explicit Init_SensorSuite_gyro_x(::bzzz_msgs::msg::SensorSuite & msg)
  : msg_(msg)
  {}
  Init_SensorSuite_gyro_y gyro_x(::bzzz_msgs::msg::SensorSuite::_gyro_x_type arg)
  {
    msg_.gyro_x = std::move(arg);
    return Init_SensorSuite_gyro_y(msg_);
  }

private:
  ::bzzz_msgs::msg::SensorSuite msg_;
};

class Init_SensorSuite_accel_z
{
public:
  explicit Init_SensorSuite_accel_z(::bzzz_msgs::msg::SensorSuite & msg)
  : msg_(msg)
  {}
  Init_SensorSuite_gyro_x accel_z(::bzzz_msgs::msg::SensorSuite::_accel_z_type arg)
  {
    msg_.accel_z = std::move(arg);
    return Init_SensorSuite_gyro_x(msg_);
  }

private:
  ::bzzz_msgs::msg::SensorSuite msg_;
};

class Init_SensorSuite_accel_y
{
public:
  explicit Init_SensorSuite_accel_y(::bzzz_msgs::msg::SensorSuite & msg)
  : msg_(msg)
  {}
  Init_SensorSuite_accel_z accel_y(::bzzz_msgs::msg::SensorSuite::_accel_y_type arg)
  {
    msg_.accel_y = std::move(arg);
    return Init_SensorSuite_accel_z(msg_);
  }

private:
  ::bzzz_msgs::msg::SensorSuite msg_;
};

class Init_SensorSuite_accel_x
{
public:
  Init_SensorSuite_accel_x()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_SensorSuite_accel_y accel_x(::bzzz_msgs::msg::SensorSuite::_accel_x_type arg)
  {
    msg_.accel_x = std::move(arg);
    return Init_SensorSuite_accel_y(msg_);
  }

private:
  ::bzzz_msgs::msg::SensorSuite msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::bzzz_msgs::msg::SensorSuite>()
{
  return bzzz_msgs::msg::builder::Init_SensorSuite_accel_x();
}

}  // namespace bzzz_msgs

#endif  // BZZZ_MSGS__MSG__DETAIL__SENSOR_SUITE__BUILDER_HPP_
