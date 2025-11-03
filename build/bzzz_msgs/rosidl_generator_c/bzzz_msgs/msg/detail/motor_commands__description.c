// generated from rosidl_generator_c/resource/idl__description.c.em
// with input from bzzz_msgs:msg/MotorCommands.idl
// generated code does not contain a copyright notice

#include "bzzz_msgs/msg/detail/motor_commands__functions.h"

ROSIDL_GENERATOR_C_PUBLIC_bzzz_msgs
const rosidl_type_hash_t *
bzzz_msgs__msg__MotorCommands__get_type_hash(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_type_hash_t hash = {1, {
      0x41, 0x21, 0x12, 0x7b, 0x57, 0xa6, 0x70, 0xbd,
      0xae, 0x13, 0x97, 0x4d, 0xba, 0x0d, 0xee, 0x5b,
      0x34, 0x67, 0x7b, 0x72, 0x86, 0xac, 0xc5, 0x05,
      0x69, 0x61, 0x08, 0x65, 0x4e, 0x4d, 0xb9, 0x3e,
    }};
  return &hash;
}

#include <assert.h>
#include <string.h>

// Include directives for referenced types

// Hashes for external referenced types
#ifndef NDEBUG
#endif

static char bzzz_msgs__msg__MotorCommands__TYPE_NAME[] = "bzzz_msgs/msg/MotorCommands";

// Define type names, field names, and default values
static char bzzz_msgs__msg__MotorCommands__FIELD_NAME__thrust[] = "thrust";
static char bzzz_msgs__msg__MotorCommands__FIELD_NAME__roll[] = "roll";
static char bzzz_msgs__msg__MotorCommands__FIELD_NAME__pitch[] = "pitch";
static char bzzz_msgs__msg__MotorCommands__FIELD_NAME__yaw_rate[] = "yaw_rate";

static rosidl_runtime_c__type_description__Field bzzz_msgs__msg__MotorCommands__FIELDS[] = {
  {
    {bzzz_msgs__msg__MotorCommands__FIELD_NAME__thrust, 6, 6},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_FLOAT,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {bzzz_msgs__msg__MotorCommands__FIELD_NAME__roll, 4, 4},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_FLOAT,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {bzzz_msgs__msg__MotorCommands__FIELD_NAME__pitch, 5, 5},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_FLOAT,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {bzzz_msgs__msg__MotorCommands__FIELD_NAME__yaw_rate, 8, 8},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_FLOAT,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
};

const rosidl_runtime_c__type_description__TypeDescription *
bzzz_msgs__msg__MotorCommands__get_type_description(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static bool constructed = false;
  static const rosidl_runtime_c__type_description__TypeDescription description = {
    {
      {bzzz_msgs__msg__MotorCommands__TYPE_NAME, 27, 27},
      {bzzz_msgs__msg__MotorCommands__FIELDS, 4, 4},
    },
    {NULL, 0, 0},
  };
  if (!constructed) {
    constructed = true;
  }
  return &description;
}

static char toplevel_type_raw_source[] =
  "float32 thrust\n"
  "float32 roll\n"
  "float32 pitch\n"
  "float32 yaw_rate";

static char msg_encoding[] = "msg";

// Define all individual source functions

const rosidl_runtime_c__type_description__TypeSource *
bzzz_msgs__msg__MotorCommands__get_individual_type_description_source(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static const rosidl_runtime_c__type_description__TypeSource source = {
    {bzzz_msgs__msg__MotorCommands__TYPE_NAME, 27, 27},
    {msg_encoding, 3, 3},
    {toplevel_type_raw_source, 58, 58},
  };
  return &source;
}

const rosidl_runtime_c__type_description__TypeSource__Sequence *
bzzz_msgs__msg__MotorCommands__get_type_description_sources(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_runtime_c__type_description__TypeSource sources[1];
  static const rosidl_runtime_c__type_description__TypeSource__Sequence source_sequence = {sources, 1, 1};
  static bool constructed = false;
  if (!constructed) {
    sources[0] = *bzzz_msgs__msg__MotorCommands__get_individual_type_description_source(NULL),
    constructed = true;
  }
  return &source_sequence;
}
