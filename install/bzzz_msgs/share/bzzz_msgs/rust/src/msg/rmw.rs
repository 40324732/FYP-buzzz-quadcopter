#[cfg(feature = "serde")]
use serde::{Deserialize, Serialize};


#[link(name = "bzzz_msgs__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__bzzz_msgs__msg__MotorCommands() -> *const std::ffi::c_void;
}

#[link(name = "bzzz_msgs__rosidl_generator_c")]
extern "C" {
    fn bzzz_msgs__msg__MotorCommands__init(msg: *mut MotorCommands) -> bool;
    fn bzzz_msgs__msg__MotorCommands__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<MotorCommands>, size: usize) -> bool;
    fn bzzz_msgs__msg__MotorCommands__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<MotorCommands>);
    fn bzzz_msgs__msg__MotorCommands__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<MotorCommands>, out_seq: *mut rosidl_runtime_rs::Sequence<MotorCommands>) -> bool;
}

// Corresponds to bzzz_msgs__msg__MotorCommands
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct MotorCommands {

    // This member is not documented.
    #[allow(missing_docs)]
    pub thrust: f32,


    // This member is not documented.
    #[allow(missing_docs)]
    pub roll: f32,


    // This member is not documented.
    #[allow(missing_docs)]
    pub pitch: f32,


    // This member is not documented.
    #[allow(missing_docs)]
    pub yaw_rate: f32,

}



impl Default for MotorCommands {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !bzzz_msgs__msg__MotorCommands__init(&mut msg as *mut _) {
        panic!("Call to bzzz_msgs__msg__MotorCommands__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for MotorCommands {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { bzzz_msgs__msg__MotorCommands__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { bzzz_msgs__msg__MotorCommands__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { bzzz_msgs__msg__MotorCommands__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for MotorCommands {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for MotorCommands where Self: Sized {
  const TYPE_NAME: &'static str = "bzzz_msgs/msg/MotorCommands";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__bzzz_msgs__msg__MotorCommands() }
  }
}


#[link(name = "bzzz_msgs__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__bzzz_msgs__msg__SensorSuite() -> *const std::ffi::c_void;
}

#[link(name = "bzzz_msgs__rosidl_generator_c")]
extern "C" {
    fn bzzz_msgs__msg__SensorSuite__init(msg: *mut SensorSuite) -> bool;
    fn bzzz_msgs__msg__SensorSuite__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<SensorSuite>, size: usize) -> bool;
    fn bzzz_msgs__msg__SensorSuite__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<SensorSuite>);
    fn bzzz_msgs__msg__SensorSuite__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<SensorSuite>, out_seq: *mut rosidl_runtime_rs::Sequence<SensorSuite>) -> bool;
}

// Corresponds to bzzz_msgs__msg__SensorSuite
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]

/// Raw IMU Accelerometer Data (m/s^2)

#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct SensorSuite {

    // This member is not documented.
    #[allow(missing_docs)]
    pub accel_x: f32,


    // This member is not documented.
    #[allow(missing_docs)]
    pub accel_y: f32,


    // This member is not documented.
    #[allow(missing_docs)]
    pub accel_z: f32,

    /// Raw IMU Gyroscope Data (rad/s)
    pub gyro_x: f32,


    // This member is not documented.
    #[allow(missing_docs)]
    pub gyro_y: f32,


    // This member is not documented.
    #[allow(missing_docs)]
    pub gyro_z: f32,

    /// Altitude Sensors
    /// Distance from ToF in meters
    pub tof_distance: f32,

    /// Pressure from Barometer in Pascals
    pub baro_pressure: f32,

}



impl Default for SensorSuite {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !bzzz_msgs__msg__SensorSuite__init(&mut msg as *mut _) {
        panic!("Call to bzzz_msgs__msg__SensorSuite__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for SensorSuite {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { bzzz_msgs__msg__SensorSuite__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { bzzz_msgs__msg__SensorSuite__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { bzzz_msgs__msg__SensorSuite__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for SensorSuite {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for SensorSuite where Self: Sized {
  const TYPE_NAME: &'static str = "bzzz_msgs/msg/SensorSuite";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__bzzz_msgs__msg__SensorSuite() }
  }
}


