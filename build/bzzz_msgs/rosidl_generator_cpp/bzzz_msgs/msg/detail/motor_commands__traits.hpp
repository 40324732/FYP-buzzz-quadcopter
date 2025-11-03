// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from bzzz_msgs:msg/MotorCommands.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "bzzz_msgs/msg/motor_commands.hpp"


#ifndef BZZZ_MSGS__MSG__DETAIL__MOTOR_COMMANDS__TRAITS_HPP_
#define BZZZ_MSGS__MSG__DETAIL__MOTOR_COMMANDS__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "bzzz_msgs/msg/detail/motor_commands__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace bzzz_msgs
{

namespace msg
{

inline void to_flow_style_yaml(
  const MotorCommands & msg,
  std::ostream & out)
{
  out << "{";
  // member: thrust
  {
    out << "thrust: ";
    rosidl_generator_traits::value_to_yaml(msg.thrust, out);
    out << ", ";
  }

  // member: roll
  {
    out << "roll: ";
    rosidl_generator_traits::value_to_yaml(msg.roll, out);
    out << ", ";
  }

  // member: pitch
  {
    out << "pitch: ";
    rosidl_generator_traits::value_to_yaml(msg.pitch, out);
    out << ", ";
  }

  // member: yaw_rate
  {
    out << "yaw_rate: ";
    rosidl_generator_traits::value_to_yaml(msg.yaw_rate, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const MotorCommands & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: thrust
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "thrust: ";
    rosidl_generator_traits::value_to_yaml(msg.thrust, out);
    out << "\n";
  }

  // member: roll
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "roll: ";
    rosidl_generator_traits::value_to_yaml(msg.roll, out);
    out << "\n";
  }

  // member: pitch
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "pitch: ";
    rosidl_generator_traits::value_to_yaml(msg.pitch, out);
    out << "\n";
  }

  // member: yaw_rate
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "yaw_rate: ";
    rosidl_generator_traits::value_to_yaml(msg.yaw_rate, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const MotorCommands & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace msg

}  // namespace bzzz_msgs

namespace rosidl_generator_traits
{

[[deprecated("use bzzz_msgs::msg::to_block_style_yaml() instead")]]
inline void to_yaml(
  const bzzz_msgs::msg::MotorCommands & msg,
  std::ostream & out, size_t indentation = 0)
{
  bzzz_msgs::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use bzzz_msgs::msg::to_yaml() instead")]]
inline std::string to_yaml(const bzzz_msgs::msg::MotorCommands & msg)
{
  return bzzz_msgs::msg::to_yaml(msg);
}

template<>
inline const char * data_type<bzzz_msgs::msg::MotorCommands>()
{
  return "bzzz_msgs::msg::MotorCommands";
}

template<>
inline const char * name<bzzz_msgs::msg::MotorCommands>()
{
  return "bzzz_msgs/msg/MotorCommands";
}

template<>
struct has_fixed_size<bzzz_msgs::msg::MotorCommands>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<bzzz_msgs::msg::MotorCommands>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<bzzz_msgs::msg::MotorCommands>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // BZZZ_MSGS__MSG__DETAIL__MOTOR_COMMANDS__TRAITS_HPP_
