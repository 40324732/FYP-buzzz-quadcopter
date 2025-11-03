// generated from rosidl_generator_c/resource/idl__functions.h.em
// with input from bzzz_msgs:msg/MotorCommands.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "bzzz_msgs/msg/motor_commands.h"


#ifndef BZZZ_MSGS__MSG__DETAIL__MOTOR_COMMANDS__FUNCTIONS_H_
#define BZZZ_MSGS__MSG__DETAIL__MOTOR_COMMANDS__FUNCTIONS_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stdlib.h>

#include "rosidl_runtime_c/action_type_support_struct.h"
#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_runtime_c/service_type_support_struct.h"
#include "rosidl_runtime_c/type_description/type_description__struct.h"
#include "rosidl_runtime_c/type_description/type_source__struct.h"
#include "rosidl_runtime_c/type_hash.h"
#include "rosidl_runtime_c/visibility_control.h"
#include "bzzz_msgs/msg/rosidl_generator_c__visibility_control.h"

#include "bzzz_msgs/msg/detail/motor_commands__struct.h"

/// Initialize msg/MotorCommands message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * bzzz_msgs__msg__MotorCommands
 * )) before or use
 * bzzz_msgs__msg__MotorCommands__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_bzzz_msgs
bool
bzzz_msgs__msg__MotorCommands__init(bzzz_msgs__msg__MotorCommands * msg);

/// Finalize msg/MotorCommands message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_bzzz_msgs
void
bzzz_msgs__msg__MotorCommands__fini(bzzz_msgs__msg__MotorCommands * msg);

/// Create msg/MotorCommands message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * bzzz_msgs__msg__MotorCommands__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_bzzz_msgs
bzzz_msgs__msg__MotorCommands *
bzzz_msgs__msg__MotorCommands__create(void);

/// Destroy msg/MotorCommands message.
/**
 * It calls
 * bzzz_msgs__msg__MotorCommands__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_bzzz_msgs
void
bzzz_msgs__msg__MotorCommands__destroy(bzzz_msgs__msg__MotorCommands * msg);

/// Check for msg/MotorCommands message equality.
/**
 * \param[in] lhs The message on the left hand size of the equality operator.
 * \param[in] rhs The message on the right hand size of the equality operator.
 * \return true if messages are equal, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_bzzz_msgs
bool
bzzz_msgs__msg__MotorCommands__are_equal(const bzzz_msgs__msg__MotorCommands * lhs, const bzzz_msgs__msg__MotorCommands * rhs);

/// Copy a msg/MotorCommands message.
/**
 * This functions performs a deep copy, as opposed to the shallow copy that
 * plain assignment yields.
 *
 * \param[in] input The source message pointer.
 * \param[out] output The target message pointer, which must
 *   have been initialized before calling this function.
 * \return true if successful, or false if either pointer is null
 *   or memory allocation fails.
 */
ROSIDL_GENERATOR_C_PUBLIC_bzzz_msgs
bool
bzzz_msgs__msg__MotorCommands__copy(
  const bzzz_msgs__msg__MotorCommands * input,
  bzzz_msgs__msg__MotorCommands * output);

/// Retrieve pointer to the hash of the description of this type.
ROSIDL_GENERATOR_C_PUBLIC_bzzz_msgs
const rosidl_type_hash_t *
bzzz_msgs__msg__MotorCommands__get_type_hash(
  const rosidl_message_type_support_t * type_support);

/// Retrieve pointer to the description of this type.
ROSIDL_GENERATOR_C_PUBLIC_bzzz_msgs
const rosidl_runtime_c__type_description__TypeDescription *
bzzz_msgs__msg__MotorCommands__get_type_description(
  const rosidl_message_type_support_t * type_support);

/// Retrieve pointer to the single raw source text that defined this type.
ROSIDL_GENERATOR_C_PUBLIC_bzzz_msgs
const rosidl_runtime_c__type_description__TypeSource *
bzzz_msgs__msg__MotorCommands__get_individual_type_description_source(
  const rosidl_message_type_support_t * type_support);

/// Retrieve pointer to the recursive raw sources that defined the description of this type.
ROSIDL_GENERATOR_C_PUBLIC_bzzz_msgs
const rosidl_runtime_c__type_description__TypeSource__Sequence *
bzzz_msgs__msg__MotorCommands__get_type_description_sources(
  const rosidl_message_type_support_t * type_support);

/// Initialize array of msg/MotorCommands messages.
/**
 * It allocates the memory for the number of elements and calls
 * bzzz_msgs__msg__MotorCommands__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_bzzz_msgs
bool
bzzz_msgs__msg__MotorCommands__Sequence__init(bzzz_msgs__msg__MotorCommands__Sequence * array, size_t size);

/// Finalize array of msg/MotorCommands messages.
/**
 * It calls
 * bzzz_msgs__msg__MotorCommands__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_bzzz_msgs
void
bzzz_msgs__msg__MotorCommands__Sequence__fini(bzzz_msgs__msg__MotorCommands__Sequence * array);

/// Create array of msg/MotorCommands messages.
/**
 * It allocates the memory for the array and calls
 * bzzz_msgs__msg__MotorCommands__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_bzzz_msgs
bzzz_msgs__msg__MotorCommands__Sequence *
bzzz_msgs__msg__MotorCommands__Sequence__create(size_t size);

/// Destroy array of msg/MotorCommands messages.
/**
 * It calls
 * bzzz_msgs__msg__MotorCommands__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_bzzz_msgs
void
bzzz_msgs__msg__MotorCommands__Sequence__destroy(bzzz_msgs__msg__MotorCommands__Sequence * array);

/// Check for msg/MotorCommands message array equality.
/**
 * \param[in] lhs The message array on the left hand size of the equality operator.
 * \param[in] rhs The message array on the right hand size of the equality operator.
 * \return true if message arrays are equal in size and content, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_bzzz_msgs
bool
bzzz_msgs__msg__MotorCommands__Sequence__are_equal(const bzzz_msgs__msg__MotorCommands__Sequence * lhs, const bzzz_msgs__msg__MotorCommands__Sequence * rhs);

/// Copy an array of msg/MotorCommands messages.
/**
 * This functions performs a deep copy, as opposed to the shallow copy that
 * plain assignment yields.
 *
 * \param[in] input The source array pointer.
 * \param[out] output The target array pointer, which must
 *   have been initialized before calling this function.
 * \return true if successful, or false if either pointer
 *   is null or memory allocation fails.
 */
ROSIDL_GENERATOR_C_PUBLIC_bzzz_msgs
bool
bzzz_msgs__msg__MotorCommands__Sequence__copy(
  const bzzz_msgs__msg__MotorCommands__Sequence * input,
  bzzz_msgs__msg__MotorCommands__Sequence * output);

#ifdef __cplusplus
}
#endif

#endif  // BZZZ_MSGS__MSG__DETAIL__MOTOR_COMMANDS__FUNCTIONS_H_
