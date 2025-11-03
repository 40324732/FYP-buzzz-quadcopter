// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from bzzz_msgs:msg/SensorSuite.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "bzzz_msgs/msg/sensor_suite.hpp"


#ifndef BZZZ_MSGS__MSG__DETAIL__SENSOR_SUITE__TRAITS_HPP_
#define BZZZ_MSGS__MSG__DETAIL__SENSOR_SUITE__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "bzzz_msgs/msg/detail/sensor_suite__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace bzzz_msgs
{

namespace msg
{

inline void to_flow_style_yaml(
  const SensorSuite & msg,
  std::ostream & out)
{
  out << "{";
  // member: accel_x
  {
    out << "accel_x: ";
    rosidl_generator_traits::value_to_yaml(msg.accel_x, out);
    out << ", ";
  }

  // member: accel_y
  {
    out << "accel_y: ";
    rosidl_generator_traits::value_to_yaml(msg.accel_y, out);
    out << ", ";
  }

  // member: accel_z
  {
    out << "accel_z: ";
    rosidl_generator_traits::value_to_yaml(msg.accel_z, out);
    out << ", ";
  }

  // member: gyro_x
  {
    out << "gyro_x: ";
    rosidl_generator_traits::value_to_yaml(msg.gyro_x, out);
    out << ", ";
  }

  // member: gyro_y
  {
    out << "gyro_y: ";
    rosidl_generator_traits::value_to_yaml(msg.gyro_y, out);
    out << ", ";
  }

  // member: gyro_z
  {
    out << "gyro_z: ";
    rosidl_generator_traits::value_to_yaml(msg.gyro_z, out);
    out << ", ";
  }

  // member: tof_distance
  {
    out << "tof_distance: ";
    rosidl_generator_traits::value_to_yaml(msg.tof_distance, out);
    out << ", ";
  }

  // member: baro_pressure
  {
    out << "baro_pressure: ";
    rosidl_generator_traits::value_to_yaml(msg.baro_pressure, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const SensorSuite & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: accel_x
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "accel_x: ";
    rosidl_generator_traits::value_to_yaml(msg.accel_x, out);
    out << "\n";
  }

  // member: accel_y
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "accel_y: ";
    rosidl_generator_traits::value_to_yaml(msg.accel_y, out);
    out << "\n";
  }

  // member: accel_z
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "accel_z: ";
    rosidl_generator_traits::value_to_yaml(msg.accel_z, out);
    out << "\n";
  }

  // member: gyro_x
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "gyro_x: ";
    rosidl_generator_traits::value_to_yaml(msg.gyro_x, out);
    out << "\n";
  }

  // member: gyro_y
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "gyro_y: ";
    rosidl_generator_traits::value_to_yaml(msg.gyro_y, out);
    out << "\n";
  }

  // member: gyro_z
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "gyro_z: ";
    rosidl_generator_traits::value_to_yaml(msg.gyro_z, out);
    out << "\n";
  }

  // member: tof_distance
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "tof_distance: ";
    rosidl_generator_traits::value_to_yaml(msg.tof_distance, out);
    out << "\n";
  }

  // member: baro_pressure
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "baro_pressure: ";
    rosidl_generator_traits::value_to_yaml(msg.baro_pressure, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const SensorSuite & msg, bool use_flow_style = false)
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
  const bzzz_msgs::msg::SensorSuite & msg,
  std::ostream & out, size_t indentation = 0)
{
  bzzz_msgs::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use bzzz_msgs::msg::to_yaml() instead")]]
inline std::string to_yaml(const bzzz_msgs::msg::SensorSuite & msg)
{
  return bzzz_msgs::msg::to_yaml(msg);
}

template<>
inline const char * data_type<bzzz_msgs::msg::SensorSuite>()
{
  return "bzzz_msgs::msg::SensorSuite";
}

template<>
inline const char * name<bzzz_msgs::msg::SensorSuite>()
{
  return "bzzz_msgs/msg/SensorSuite";
}

template<>
struct has_fixed_size<bzzz_msgs::msg::SensorSuite>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<bzzz_msgs::msg::SensorSuite>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<bzzz_msgs::msg::SensorSuite>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // BZZZ_MSGS__MSG__DETAIL__SENSOR_SUITE__TRAITS_HPP_
