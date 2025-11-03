// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from bzzz_msgs:msg/MotorCommands.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "bzzz_msgs/msg/motor_commands.hpp"


#ifndef BZZZ_MSGS__MSG__DETAIL__MOTOR_COMMANDS__STRUCT_HPP_
#define BZZZ_MSGS__MSG__DETAIL__MOTOR_COMMANDS__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__bzzz_msgs__msg__MotorCommands __attribute__((deprecated))
#else
# define DEPRECATED__bzzz_msgs__msg__MotorCommands __declspec(deprecated)
#endif

namespace bzzz_msgs
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct MotorCommands_
{
  using Type = MotorCommands_<ContainerAllocator>;

  explicit MotorCommands_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->thrust = 0.0f;
      this->roll = 0.0f;
      this->pitch = 0.0f;
      this->yaw_rate = 0.0f;
    }
  }

  explicit MotorCommands_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->thrust = 0.0f;
      this->roll = 0.0f;
      this->pitch = 0.0f;
      this->yaw_rate = 0.0f;
    }
  }

  // field types and members
  using _thrust_type =
    float;
  _thrust_type thrust;
  using _roll_type =
    float;
  _roll_type roll;
  using _pitch_type =
    float;
  _pitch_type pitch;
  using _yaw_rate_type =
    float;
  _yaw_rate_type yaw_rate;

  // setters for named parameter idiom
  Type & set__thrust(
    const float & _arg)
  {
    this->thrust = _arg;
    return *this;
  }
  Type & set__roll(
    const float & _arg)
  {
    this->roll = _arg;
    return *this;
  }
  Type & set__pitch(
    const float & _arg)
  {
    this->pitch = _arg;
    return *this;
  }
  Type & set__yaw_rate(
    const float & _arg)
  {
    this->yaw_rate = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    bzzz_msgs::msg::MotorCommands_<ContainerAllocator> *;
  using ConstRawPtr =
    const bzzz_msgs::msg::MotorCommands_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<bzzz_msgs::msg::MotorCommands_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<bzzz_msgs::msg::MotorCommands_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      bzzz_msgs::msg::MotorCommands_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<bzzz_msgs::msg::MotorCommands_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      bzzz_msgs::msg::MotorCommands_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<bzzz_msgs::msg::MotorCommands_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<bzzz_msgs::msg::MotorCommands_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<bzzz_msgs::msg::MotorCommands_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__bzzz_msgs__msg__MotorCommands
    std::shared_ptr<bzzz_msgs::msg::MotorCommands_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__bzzz_msgs__msg__MotorCommands
    std::shared_ptr<bzzz_msgs::msg::MotorCommands_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const MotorCommands_ & other) const
  {
    if (this->thrust != other.thrust) {
      return false;
    }
    if (this->roll != other.roll) {
      return false;
    }
    if (this->pitch != other.pitch) {
      return false;
    }
    if (this->yaw_rate != other.yaw_rate) {
      return false;
    }
    return true;
  }
  bool operator!=(const MotorCommands_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct MotorCommands_

// alias to use template instance with default allocator
using MotorCommands =
  bzzz_msgs::msg::MotorCommands_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace bzzz_msgs

#endif  // BZZZ_MSGS__MSG__DETAIL__MOTOR_COMMANDS__STRUCT_HPP_
