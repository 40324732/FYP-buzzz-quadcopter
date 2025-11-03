// generated from rosidl_generator_c/resource/idl__description.c.em
// with input from bzzz_msgs:msg/SensorSuite.idl
// generated code does not contain a copyright notice

#include "bzzz_msgs/msg/detail/sensor_suite__functions.h"

ROSIDL_GENERATOR_C_PUBLIC_bzzz_msgs
const rosidl_type_hash_t *
bzzz_msgs__msg__SensorSuite__get_type_hash(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_type_hash_t hash = {1, {
      0x24, 0xff, 0xa2, 0xbe, 0x5d, 0xa6, 0xa4, 0x2e,
      0x72, 0x71, 0xe3, 0x57, 0x28, 0x32, 0xed, 0x56,
      0x6b, 0xaf, 0xa1, 0xe6, 0x5e, 0xa1, 0x23, 0xfb,
      0x69, 0xf7, 0x55, 0x9e, 0x94, 0x44, 0x59, 0xb1,
    }};
  return &hash;
}

#include <assert.h>
#include <string.h>

// Include directives for referenced types

// Hashes for external referenced types
#ifndef NDEBUG
#endif

static char bzzz_msgs__msg__SensorSuite__TYPE_NAME[] = "bzzz_msgs/msg/SensorSuite";

// Define type names, field names, and default values
static char bzzz_msgs__msg__SensorSuite__FIELD_NAME__accel_x[] = "accel_x";
static char bzzz_msgs__msg__SensorSuite__FIELD_NAME__accel_y[] = "accel_y";
static char bzzz_msgs__msg__SensorSuite__FIELD_NAME__accel_z[] = "accel_z";
static char bzzz_msgs__msg__SensorSuite__FIELD_NAME__gyro_x[] = "gyro_x";
static char bzzz_msgs__msg__SensorSuite__FIELD_NAME__gyro_y[] = "gyro_y";
static char bzzz_msgs__msg__SensorSuite__FIELD_NAME__gyro_z[] = "gyro_z";
static char bzzz_msgs__msg__SensorSuite__FIELD_NAME__tof_distance[] = "tof_distance";
static char bzzz_msgs__msg__SensorSuite__FIELD_NAME__baro_pressure[] = "baro_pressure";

static rosidl_runtime_c__type_description__Field bzzz_msgs__msg__SensorSuite__FIELDS[] = {
  {
    {bzzz_msgs__msg__SensorSuite__FIELD_NAME__accel_x, 7, 7},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_FLOAT,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {bzzz_msgs__msg__SensorSuite__FIELD_NAME__accel_y, 7, 7},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_FLOAT,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {bzzz_msgs__msg__SensorSuite__FIELD_NAME__accel_z, 7, 7},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_FLOAT,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {bzzz_msgs__msg__SensorSuite__FIELD_NAME__gyro_x, 6, 6},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_FLOAT,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {bzzz_msgs__msg__SensorSuite__FIELD_NAME__gyro_y, 6, 6},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_FLOAT,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {bzzz_msgs__msg__SensorSuite__FIELD_NAME__gyro_z, 6, 6},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_FLOAT,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {bzzz_msgs__msg__SensorSuite__FIELD_NAME__tof_distance, 12, 12},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_FLOAT,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {bzzz_msgs__msg__SensorSuite__FIELD_NAME__baro_pressure, 13, 13},
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
bzzz_msgs__msg__SensorSuite__get_type_description(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static bool constructed = false;
  static const rosidl_runtime_c__type_description__TypeDescription description = {
    {
      {bzzz_msgs__msg__SensorSuite__TYPE_NAME, 25, 25},
      {bzzz_msgs__msg__SensorSuite__FIELDS, 8, 8},
    },
    {NULL, 0, 0},
  };
  if (!constructed) {
    constructed = true;
  }
  return &description;
}

static char toplevel_type_raw_source[] =
  "# Raw IMU Accelerometer Data (m/s^2)\n"
  "float32 accel_x\n"
  "float32 accel_y\n"
  "float32 accel_z\n"
  "\n"
  "# Raw IMU Gyroscope Data (rad/s)\n"
  "float32 gyro_x\n"
  "float32 gyro_y\n"
  "float32 gyro_z\n"
  "\n"
  "# Altitude Sensors\n"
  "float32 tof_distance      # Distance from ToF in meters\n"
  "float32 baro_pressure     # Pressure from Barometer in Pascals";

static char msg_encoding[] = "msg";

// Define all individual source functions

const rosidl_runtime_c__type_description__TypeSource *
bzzz_msgs__msg__SensorSuite__get_individual_type_description_source(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static const rosidl_runtime_c__type_description__TypeSource source = {
    {bzzz_msgs__msg__SensorSuite__TYPE_NAME, 25, 25},
    {msg_encoding, 3, 3},
    {toplevel_type_raw_source, 302, 302},
  };
  return &source;
}

const rosidl_runtime_c__type_description__TypeSource__Sequence *
bzzz_msgs__msg__SensorSuite__get_type_description_sources(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_runtime_c__type_description__TypeSource sources[1];
  static const rosidl_runtime_c__type_description__TypeSource__Sequence source_sequence = {sources, 1, 1};
  static bool constructed = false;
  if (!constructed) {
    sources[0] = *bzzz_msgs__msg__SensorSuite__get_individual_type_description_source(NULL),
    constructed = true;
  }
  return &source_sequence;
}
