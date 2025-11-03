// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from bzzz_msgs:msg/SensorSuite.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "bzzz_msgs/msg/sensor_suite.hpp"


#ifndef BZZZ_MSGS__MSG__DETAIL__SENSOR_SUITE__STRUCT_HPP_
#define BZZZ_MSGS__MSG__DETAIL__SENSOR_SUITE__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__bzzz_msgs__msg__SensorSuite __attribute__((deprecated))
#else
# define DEPRECATED__bzzz_msgs__msg__SensorSuite __declspec(deprecated)
#endif

namespace bzzz_msgs
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct SensorSuite_
{
  using Type = SensorSuite_<ContainerAllocator>;

  explicit SensorSuite_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->accel_x = 0.0f;
      this->accel_y = 0.0f;
      this->accel_z = 0.0f;
      this->gyro_x = 0.0f;
      this->gyro_y = 0.0f;
      this->gyro_z = 0.0f;
      this->tof_distance = 0.0f;
      this->baro_pressure = 0.0f;
    }
  }

  explicit SensorSuite_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->accel_x = 0.0f;
      this->accel_y = 0.0f;
      this->accel_z = 0.0f;
      this->gyro_x = 0.0f;
      this->gyro_y = 0.0f;
      this->gyro_z = 0.0f;
      this->tof_distance = 0.0f;
      this->baro_pressure = 0.0f;
    }
  }

  // field types and members
  using _accel_x_type =
    float;
  _accel_x_type accel_x;
  using _accel_y_type =
    float;
  _accel_y_type accel_y;
  using _accel_z_type =
    float;
  _accel_z_type accel_z;
  using _gyro_x_type =
    float;
  _gyro_x_type gyro_x;
  using _gyro_y_type =
    float;
  _gyro_y_type gyro_y;
  using _gyro_z_type =
    float;
  _gyro_z_type gyro_z;
  using _tof_distance_type =
    float;
  _tof_distance_type tof_distance;
  using _baro_pressure_type =
    float;
  _baro_pressure_type baro_pressure;

  // setters for named parameter idiom
  Type & set__accel_x(
    const float & _arg)
  {
    this->accel_x = _arg;
    return *this;
  }
  Type & set__accel_y(
    const float & _arg)
  {
    this->accel_y = _arg;
    return *this;
  }
  Type & set__accel_z(
    const float & _arg)
  {
    this->accel_z = _arg;
    return *this;
  }
  Type & set__gyro_x(
    const float & _arg)
  {
    this->gyro_x = _arg;
    return *this;
  }
  Type & set__gyro_y(
    const float & _arg)
  {
    this->gyro_y = _arg;
    return *this;
  }
  Type & set__gyro_z(
    const float & _arg)
  {
    this->gyro_z = _arg;
    return *this;
  }
  Type & set__tof_distance(
    const float & _arg)
  {
    this->tof_distance = _arg;
    return *this;
  }
  Type & set__baro_pressure(
    const float & _arg)
  {
    this->baro_pressure = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    bzzz_msgs::msg::SensorSuite_<ContainerAllocator> *;
  using ConstRawPtr =
    const bzzz_msgs::msg::SensorSuite_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<bzzz_msgs::msg::SensorSuite_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<bzzz_msgs::msg::SensorSuite_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      bzzz_msgs::msg::SensorSuite_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<bzzz_msgs::msg::SensorSuite_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      bzzz_msgs::msg::SensorSuite_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<bzzz_msgs::msg::SensorSuite_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<bzzz_msgs::msg::SensorSuite_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<bzzz_msgs::msg::SensorSuite_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__bzzz_msgs__msg__SensorSuite
    std::shared_ptr<bzzz_msgs::msg::SensorSuite_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__bzzz_msgs__msg__SensorSuite
    std::shared_ptr<bzzz_msgs::msg::SensorSuite_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const SensorSuite_ & other) const
  {
    if (this->accel_x != other.accel_x) {
      return false;
    }
    if (this->accel_y != other.accel_y) {
      return false;
    }
    if (this->accel_z != other.accel_z) {
      return false;
    }
    if (this->gyro_x != other.gyro_x) {
      return false;
    }
    if (this->gyro_y != other.gyro_y) {
      return false;
    }
    if (this->gyro_z != other.gyro_z) {
      return false;
    }
    if (this->tof_distance != other.tof_distance) {
      return false;
    }
    if (this->baro_pressure != other.baro_pressure) {
      return false;
    }
    return true;
  }
  bool operator!=(const SensorSuite_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct SensorSuite_

// alias to use template instance with default allocator
using SensorSuite =
  bzzz_msgs::msg::SensorSuite_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace bzzz_msgs

#endif  // BZZZ_MSGS__MSG__DETAIL__SENSOR_SUITE__STRUCT_HPP_
