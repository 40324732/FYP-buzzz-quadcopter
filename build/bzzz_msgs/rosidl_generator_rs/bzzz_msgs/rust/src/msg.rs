#[cfg(feature = "serde")]
use serde::{Deserialize, Serialize};



// Corresponds to bzzz_msgs__msg__MotorCommands

// This struct is not documented.
#[allow(missing_docs)]

#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
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
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::msg::rmw::MotorCommands::default())
  }
}

impl rosidl_runtime_rs::Message for MotorCommands {
  type RmwMsg = super::msg::rmw::MotorCommands;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        thrust: msg.thrust,
        roll: msg.roll,
        pitch: msg.pitch,
        yaw_rate: msg.yaw_rate,
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
      thrust: msg.thrust,
      roll: msg.roll,
      pitch: msg.pitch,
      yaw_rate: msg.yaw_rate,
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      thrust: msg.thrust,
      roll: msg.roll,
      pitch: msg.pitch,
      yaw_rate: msg.yaw_rate,
    }
  }
}


// Corresponds to bzzz_msgs__msg__SensorSuite
/// Raw IMU Accelerometer Data (m/s^2)

#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
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
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::msg::rmw::SensorSuite::default())
  }
}

impl rosidl_runtime_rs::Message for SensorSuite {
  type RmwMsg = super::msg::rmw::SensorSuite;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        accel_x: msg.accel_x,
        accel_y: msg.accel_y,
        accel_z: msg.accel_z,
        gyro_x: msg.gyro_x,
        gyro_y: msg.gyro_y,
        gyro_z: msg.gyro_z,
        tof_distance: msg.tof_distance,
        baro_pressure: msg.baro_pressure,
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
      accel_x: msg.accel_x,
      accel_y: msg.accel_y,
      accel_z: msg.accel_z,
      gyro_x: msg.gyro_x,
      gyro_y: msg.gyro_y,
      gyro_z: msg.gyro_z,
      tof_distance: msg.tof_distance,
      baro_pressure: msg.baro_pressure,
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      accel_x: msg.accel_x,
      accel_y: msg.accel_y,
      accel_z: msg.accel_z,
      gyro_x: msg.gyro_x,
      gyro_y: msg.gyro_y,
      gyro_z: msg.gyro_z,
      tof_distance: msg.tof_distance,
      baro_pressure: msg.baro_pressure,
    }
  }
}


