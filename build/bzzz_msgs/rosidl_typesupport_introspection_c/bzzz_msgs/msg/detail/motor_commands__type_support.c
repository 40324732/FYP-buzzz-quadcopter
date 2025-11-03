// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from bzzz_msgs:msg/MotorCommands.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "bzzz_msgs/msg/detail/motor_commands__rosidl_typesupport_introspection_c.h"
#include "bzzz_msgs/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "bzzz_msgs/msg/detail/motor_commands__functions.h"
#include "bzzz_msgs/msg/detail/motor_commands__struct.h"


#ifdef __cplusplus
extern "C"
{
#endif

void bzzz_msgs__msg__MotorCommands__rosidl_typesupport_introspection_c__MotorCommands_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  bzzz_msgs__msg__MotorCommands__init(message_memory);
}

void bzzz_msgs__msg__MotorCommands__rosidl_typesupport_introspection_c__MotorCommands_fini_function(void * message_memory)
{
  bzzz_msgs__msg__MotorCommands__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember bzzz_msgs__msg__MotorCommands__rosidl_typesupport_introspection_c__MotorCommands_message_member_array[4] = {
  {
    "thrust",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(bzzz_msgs__msg__MotorCommands, thrust),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "roll",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(bzzz_msgs__msg__MotorCommands, roll),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "pitch",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(bzzz_msgs__msg__MotorCommands, pitch),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "yaw_rate",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(bzzz_msgs__msg__MotorCommands, yaw_rate),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers bzzz_msgs__msg__MotorCommands__rosidl_typesupport_introspection_c__MotorCommands_message_members = {
  "bzzz_msgs__msg",  // message namespace
  "MotorCommands",  // message name
  4,  // number of fields
  sizeof(bzzz_msgs__msg__MotorCommands),
  false,  // has_any_key_member_
  bzzz_msgs__msg__MotorCommands__rosidl_typesupport_introspection_c__MotorCommands_message_member_array,  // message members
  bzzz_msgs__msg__MotorCommands__rosidl_typesupport_introspection_c__MotorCommands_init_function,  // function to initialize message memory (memory has to be allocated)
  bzzz_msgs__msg__MotorCommands__rosidl_typesupport_introspection_c__MotorCommands_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t bzzz_msgs__msg__MotorCommands__rosidl_typesupport_introspection_c__MotorCommands_message_type_support_handle = {
  0,
  &bzzz_msgs__msg__MotorCommands__rosidl_typesupport_introspection_c__MotorCommands_message_members,
  get_message_typesupport_handle_function,
  &bzzz_msgs__msg__MotorCommands__get_type_hash,
  &bzzz_msgs__msg__MotorCommands__get_type_description,
  &bzzz_msgs__msg__MotorCommands__get_type_description_sources,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_bzzz_msgs
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, bzzz_msgs, msg, MotorCommands)() {
  if (!bzzz_msgs__msg__MotorCommands__rosidl_typesupport_introspection_c__MotorCommands_message_type_support_handle.typesupport_identifier) {
    bzzz_msgs__msg__MotorCommands__rosidl_typesupport_introspection_c__MotorCommands_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &bzzz_msgs__msg__MotorCommands__rosidl_typesupport_introspection_c__MotorCommands_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif
