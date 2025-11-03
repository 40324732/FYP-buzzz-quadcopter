// generated from rosidl_typesupport_fastrtps_c/resource/idl__rosidl_typesupport_fastrtps_c.h.em
// with input from bzzz_msgs:msg/MotorCommands.idl
// generated code does not contain a copyright notice
#ifndef BZZZ_MSGS__MSG__DETAIL__MOTOR_COMMANDS__ROSIDL_TYPESUPPORT_FASTRTPS_C_H_
#define BZZZ_MSGS__MSG__DETAIL__MOTOR_COMMANDS__ROSIDL_TYPESUPPORT_FASTRTPS_C_H_


#include <stddef.h>
#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_typesupport_interface/macros.h"
#include "bzzz_msgs/msg/rosidl_typesupport_fastrtps_c__visibility_control.h"
#include "bzzz_msgs/msg/detail/motor_commands__struct.h"
#include "fastcdr/Cdr.h"

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_bzzz_msgs
bool cdr_serialize_bzzz_msgs__msg__MotorCommands(
  const bzzz_msgs__msg__MotorCommands * ros_message,
  eprosima::fastcdr::Cdr & cdr);

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_bzzz_msgs
bool cdr_deserialize_bzzz_msgs__msg__MotorCommands(
  eprosima::fastcdr::Cdr &,
  bzzz_msgs__msg__MotorCommands * ros_message);

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_bzzz_msgs
size_t get_serialized_size_bzzz_msgs__msg__MotorCommands(
  const void * untyped_ros_message,
  size_t current_alignment);

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_bzzz_msgs
size_t max_serialized_size_bzzz_msgs__msg__MotorCommands(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment);

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_bzzz_msgs
bool cdr_serialize_key_bzzz_msgs__msg__MotorCommands(
  const bzzz_msgs__msg__MotorCommands * ros_message,
  eprosima::fastcdr::Cdr & cdr);

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_bzzz_msgs
size_t get_serialized_size_key_bzzz_msgs__msg__MotorCommands(
  const void * untyped_ros_message,
  size_t current_alignment);

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_bzzz_msgs
size_t max_serialized_size_key_bzzz_msgs__msg__MotorCommands(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment);

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_bzzz_msgs
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, bzzz_msgs, msg, MotorCommands)();

#ifdef __cplusplus
}
#endif

#endif  // BZZZ_MSGS__MSG__DETAIL__MOTOR_COMMANDS__ROSIDL_TYPESUPPORT_FASTRTPS_C_H_
