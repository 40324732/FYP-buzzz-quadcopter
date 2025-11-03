// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from bzzz_msgs:msg/SensorSuite.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "bzzz_msgs/msg/sensor_suite.h"


#ifndef BZZZ_MSGS__MSG__DETAIL__SENSOR_SUITE__STRUCT_H_
#define BZZZ_MSGS__MSG__DETAIL__SENSOR_SUITE__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// Constants defined in the message

/// Struct defined in msg/SensorSuite in the package bzzz_msgs.
/**
  * Raw IMU Accelerometer Data (m/s^2)
 */
typedef struct bzzz_msgs__msg__SensorSuite
{
  float accel_x;
  float accel_y;
  float accel_z;
  /// Raw IMU Gyroscope Data (rad/s)
  float gyro_x;
  float gyro_y;
  float gyro_z;
  /// Altitude Sensors
  /// Distance from ToF in meters
  float tof_distance;
  /// Pressure from Barometer in Pascals
  float baro_pressure;
} bzzz_msgs__msg__SensorSuite;

// Struct for a sequence of bzzz_msgs__msg__SensorSuite.
typedef struct bzzz_msgs__msg__SensorSuite__Sequence
{
  bzzz_msgs__msg__SensorSuite * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} bzzz_msgs__msg__SensorSuite__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // BZZZ_MSGS__MSG__DETAIL__SENSOR_SUITE__STRUCT_H_
