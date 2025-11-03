// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from bzzz_msgs:msg/MotorCommands.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "bzzz_msgs/msg/motor_commands.hpp"


#ifndef BZZZ_MSGS__MSG__DETAIL__MOTOR_COMMANDS__BUILDER_HPP_
#define BZZZ_MSGS__MSG__DETAIL__MOTOR_COMMANDS__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "bzzz_msgs/msg/detail/motor_commands__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace bzzz_msgs
{

namespace msg
{

namespace builder
{

class Init_MotorCommands_yaw_rate
{
public:
  explicit Init_MotorCommands_yaw_rate(::bzzz_msgs::msg::MotorCommands & msg)
  : msg_(msg)
  {}
  ::bzzz_msgs::msg::MotorCommands yaw_rate(::bzzz_msgs::msg::MotorCommands::_yaw_rate_type arg)
  {
    msg_.yaw_rate = std::move(arg);
    return std::move(msg_);
  }

private:
  ::bzzz_msgs::msg::MotorCommands msg_;
};

class Init_MotorCommands_pitch
{
public:
  explicit Init_MotorCommands_pitch(::bzzz_msgs::msg::MotorCommands & msg)
  : msg_(msg)
  {}
  Init_MotorCommands_yaw_rate pitch(::bzzz_msgs::msg::MotorCommands::_pitch_type arg)
  {
    msg_.pitch = std::move(arg);
    return Init_MotorCommands_yaw_rate(msg_);
  }

private:
  ::bzzz_msgs::msg::MotorCommands msg_;
};

class Init_MotorCommands_roll
{
public:
  explicit Init_MotorCommands_roll(::bzzz_msgs::msg::MotorCommands & msg)
  : msg_(msg)
  {}
  Init_MotorCommands_pitch roll(::bzzz_msgs::msg::MotorCommands::_roll_type arg)
  {
    msg_.roll = std::move(arg);
    return Init_MotorCommands_pitch(msg_);
  }

private:
  ::bzzz_msgs::msg::MotorCommands msg_;
};

class Init_MotorCommands_thrust
{
public:
  Init_MotorCommands_thrust()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_MotorCommands_roll thrust(::bzzz_msgs::msg::MotorCommands::_thrust_type arg)
  {
    msg_.thrust = std::move(arg);
    return Init_MotorCommands_roll(msg_);
  }

private:
  ::bzzz_msgs::msg::MotorCommands msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::bzzz_msgs::msg::MotorCommands>()
{
  return bzzz_msgs::msg::builder::Init_MotorCommands_thrust();
}

}  // namespace bzzz_msgs

#endif  // BZZZ_MSGS__MSG__DETAIL__MOTOR_COMMANDS__BUILDER_HPP_
