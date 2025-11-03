// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from bzzz_msgs:msg/SensorSuite.idl
// generated code does not contain a copyright notice
#include "bzzz_msgs/msg/detail/sensor_suite__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


bool
bzzz_msgs__msg__SensorSuite__init(bzzz_msgs__msg__SensorSuite * msg)
{
  if (!msg) {
    return false;
  }
  // accel_x
  // accel_y
  // accel_z
  // gyro_x
  // gyro_y
  // gyro_z
  // tof_distance
  // baro_pressure
  return true;
}

void
bzzz_msgs__msg__SensorSuite__fini(bzzz_msgs__msg__SensorSuite * msg)
{
  if (!msg) {
    return;
  }
  // accel_x
  // accel_y
  // accel_z
  // gyro_x
  // gyro_y
  // gyro_z
  // tof_distance
  // baro_pressure
}

bool
bzzz_msgs__msg__SensorSuite__are_equal(const bzzz_msgs__msg__SensorSuite * lhs, const bzzz_msgs__msg__SensorSuite * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // accel_x
  if (lhs->accel_x != rhs->accel_x) {
    return false;
  }
  // accel_y
  if (lhs->accel_y != rhs->accel_y) {
    return false;
  }
  // accel_z
  if (lhs->accel_z != rhs->accel_z) {
    return false;
  }
  // gyro_x
  if (lhs->gyro_x != rhs->gyro_x) {
    return false;
  }
  // gyro_y
  if (lhs->gyro_y != rhs->gyro_y) {
    return false;
  }
  // gyro_z
  if (lhs->gyro_z != rhs->gyro_z) {
    return false;
  }
  // tof_distance
  if (lhs->tof_distance != rhs->tof_distance) {
    return false;
  }
  // baro_pressure
  if (lhs->baro_pressure != rhs->baro_pressure) {
    return false;
  }
  return true;
}

bool
bzzz_msgs__msg__SensorSuite__copy(
  const bzzz_msgs__msg__SensorSuite * input,
  bzzz_msgs__msg__SensorSuite * output)
{
  if (!input || !output) {
    return false;
  }
  // accel_x
  output->accel_x = input->accel_x;
  // accel_y
  output->accel_y = input->accel_y;
  // accel_z
  output->accel_z = input->accel_z;
  // gyro_x
  output->gyro_x = input->gyro_x;
  // gyro_y
  output->gyro_y = input->gyro_y;
  // gyro_z
  output->gyro_z = input->gyro_z;
  // tof_distance
  output->tof_distance = input->tof_distance;
  // baro_pressure
  output->baro_pressure = input->baro_pressure;
  return true;
}

bzzz_msgs__msg__SensorSuite *
bzzz_msgs__msg__SensorSuite__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  bzzz_msgs__msg__SensorSuite * msg = (bzzz_msgs__msg__SensorSuite *)allocator.allocate(sizeof(bzzz_msgs__msg__SensorSuite), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(bzzz_msgs__msg__SensorSuite));
  bool success = bzzz_msgs__msg__SensorSuite__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
bzzz_msgs__msg__SensorSuite__destroy(bzzz_msgs__msg__SensorSuite * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    bzzz_msgs__msg__SensorSuite__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
bzzz_msgs__msg__SensorSuite__Sequence__init(bzzz_msgs__msg__SensorSuite__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  bzzz_msgs__msg__SensorSuite * data = NULL;

  if (size) {
    data = (bzzz_msgs__msg__SensorSuite *)allocator.zero_allocate(size, sizeof(bzzz_msgs__msg__SensorSuite), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = bzzz_msgs__msg__SensorSuite__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        bzzz_msgs__msg__SensorSuite__fini(&data[i - 1]);
      }
      allocator.deallocate(data, allocator.state);
      return false;
    }
  }
  array->data = data;
  array->size = size;
  array->capacity = size;
  return true;
}

void
bzzz_msgs__msg__SensorSuite__Sequence__fini(bzzz_msgs__msg__SensorSuite__Sequence * array)
{
  if (!array) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();

  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      bzzz_msgs__msg__SensorSuite__fini(&array->data[i]);
    }
    allocator.deallocate(array->data, allocator.state);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  } else {
    // ensure that data, size, and capacity values are consistent
    assert(0 == array->size);
    assert(0 == array->capacity);
  }
}

bzzz_msgs__msg__SensorSuite__Sequence *
bzzz_msgs__msg__SensorSuite__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  bzzz_msgs__msg__SensorSuite__Sequence * array = (bzzz_msgs__msg__SensorSuite__Sequence *)allocator.allocate(sizeof(bzzz_msgs__msg__SensorSuite__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = bzzz_msgs__msg__SensorSuite__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
bzzz_msgs__msg__SensorSuite__Sequence__destroy(bzzz_msgs__msg__SensorSuite__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    bzzz_msgs__msg__SensorSuite__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
bzzz_msgs__msg__SensorSuite__Sequence__are_equal(const bzzz_msgs__msg__SensorSuite__Sequence * lhs, const bzzz_msgs__msg__SensorSuite__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!bzzz_msgs__msg__SensorSuite__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
bzzz_msgs__msg__SensorSuite__Sequence__copy(
  const bzzz_msgs__msg__SensorSuite__Sequence * input,
  bzzz_msgs__msg__SensorSuite__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(bzzz_msgs__msg__SensorSuite);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    bzzz_msgs__msg__SensorSuite * data =
      (bzzz_msgs__msg__SensorSuite *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!bzzz_msgs__msg__SensorSuite__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          bzzz_msgs__msg__SensorSuite__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!bzzz_msgs__msg__SensorSuite__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
