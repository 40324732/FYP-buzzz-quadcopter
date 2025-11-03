#include <Arduino.h>
#include <Wire.h>
#include <ESP32Servo.h>

const int M1_PIN = 13;
const int M2_PIN = 12;
const int M3_PIN = 14;
const int M4_PIN = 27;

Servo motor1, motor2, motor3, motor4;

const int MPU_ADDR = 0x68; 
float comp_angle_roll = 0.0;
float comp_angle_pitch = 0.0;

const int MIN_PWM = 1000;
const int MAX_PWM = 2000;

struct __attribute__((packed)) SerialRxPacket {
  uint8_t header1;
  uint8_t header2;
  float thrust;
  float roll;
  float pitch;
  float yaw_rate;
  uint8_t footer;
};

const int PACKET_SIZE = sizeof(SerialRxPacket);
uint8_t rx_buffer[PACKET_SIZE];
int buffer_index = 0;

enum SerialState { WAIT_FOR_AA, WAIT_FOR_BB, READ_PAYLOAD };
SerialState current_state = WAIT_FOR_AA;

float target_thrust = 0.0;
float target_roll = 0.0;
float target_pitch = 0.0;
float target_yaw_rate = 0.0;

float kp_roll = 1.2, ki_roll = 0.05, kd_roll = 0.1;
float kp_pitch = 1.2, ki_pitch = 0.05, kd_pitch = 0.1;
float kp_yaw = 2.0,  ki_yaw = 0.0,   kd_yaw = 0.0;

float roll_integral = 0, prev_roll_error = 0;
float pitch_integral = 0, prev_pitch_error = 0;
float yaw_integral = 0, prev_yaw_error = 0;

unsigned long last_time = 0;

float computePID(float target, float current, float kp, float ki, float kd, float dt, float* integral, float* prev_error) {
  float error = target - current;
  float P = kp * error;
  
  *integral += error * dt;
  *integral = constrain(*integral, -400, 400); // Anti-windup
  float I = ki * (*integral);
  
  float derivative = (error - *prev_error) / dt;
  float D = kd * derivative;
  
  *prev_error = error;
  return P + I + D;
}

void setup() {
  Serial.begin(115200);
  
  Wire.begin(); 
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(0x6B);
  Wire.write(0x00);
  Wire.endTransmission(true);

  ESP32PWM::allocateTimer(0);
  ESP32PWM::allocateTimer(1);
  ESP32PWM::allocateTimer(2);
  ESP32PWM::allocateTimer(3);

  motor1.setPeriodHertz(250); 
  motor2.setPeriodHertz(250);
  motor3.setPeriodHertz(250);
  motor4.setPeriodHertz(250);

  motor1.attach(M1_PIN, MIN_PWM, MAX_PWM);
  motor2.attach(M2_PIN, MIN_PWM, MAX_PWM);
  motor3.attach(M3_PIN, MIN_PWM, MAX_PWM);
  motor4.attach(M4_PIN, MIN_PWM, MAX_PWM);

  motor1.writeMicroseconds(MIN_PWM);
  motor2.writeMicroseconds(MIN_PWM);
  motor3.writeMicroseconds(MIN_PWM);
  motor4.writeMicroseconds(MIN_PWM);
  delay(2000); 
  
  last_time = micros();
}

// ==========================================================
// 6. MAIN SUPER-LOOP
// ==========================================================

void loop() {
  
  while (Serial.available() > 0) {
    uint8_t incoming_byte = Serial.read();

    switch (current_state) {
      case WAIT_FOR_AA:
        if (incoming_byte == 0xAA) { rx_buffer[0] = incoming_byte; current_state = WAIT_FOR_BB; }
        break;
      case WAIT_FOR_BB:
        if (incoming_byte == 0xBB) { rx_buffer[1] = incoming_byte; buffer_index = 2; current_state = READ_PAYLOAD; } 
        else if (incoming_byte == 0xAA) { current_state = WAIT_FOR_BB; } 
        else { current_state = WAIT_FOR_AA; }
        break;
      case READ_PAYLOAD:
        rx_buffer[buffer_index++] = incoming_byte;
        if (buffer_index == PACKET_SIZE) {
          SerialRxPacket* packet = (SerialRxPacket*)rx_buffer;
          if (packet->footer == 0xFF) {
            // Success! Update our global targets
            target_thrust = packet->thrust;
            target_roll = packet->roll;
            target_pitch = packet->pitch;
            target_yaw_rate = packet->yaw_rate;
          }
          current_state = WAIT_FOR_AA;
        }
        break;
    }
  }

  unsigned long current_time = micros();
  float dt = (current_time - last_time) / 1000000.0; 
  
  if (dt >= 0.004) { 
    last_time = current_time; 
    
    Wire.beginTransmission(MPU_ADDR);
    Wire.write(0x3B); 
    Wire.endTransmission(false);
    Wire.requestFrom(MPU_ADDR, 14, true); 

    int16_t accX = (Wire.read() << 8 | Wire.read());
    int16_t accY = (Wire.read() << 8 | Wire.read());
    int16_t accZ = (Wire.read() << 8 | Wire.read());
    int16_t temp = (Wire.read() << 8 | Wire.read());
    int16_t gyroX = (Wire.read() << 8 | Wire.read());
    int16_t gyroY = (Wire.read() << 8 | Wire.read());
    int16_t gyroZ = (Wire.read() << 8 | Wire.read());

    float gX = gyroX / 131.0; 
    float gY = gyroY / 131.0;
    float gZ = gyroZ / 131.0;

    float accel_roll = atan2(accY, accZ) * 180 / PI;
    float accel_pitch = atan(-accX / sqrt(accY * accY + accZ * accZ)) * 180 / PI;

    comp_angle_roll = 0.98 * (comp_angle_roll + gX * dt) + 0.02 * accel_roll;
    comp_angle_pitch = 0.98 * (comp_angle_pitch + gY * dt) + 0.02 * accel_pitch;

    float current_roll = comp_angle_roll;       
    float current_pitch = comp_angle_pitch;      
    float current_yaw_rate = gZ; 

    float roll_correction = computePID(target_roll, current_roll, kp_roll, ki_roll, kd_roll, dt, &roll_integral, &prev_roll_error);
    float pitch_correction = computePID(target_pitch, current_pitch, kp_pitch, ki_pitch, kd_pitch, dt, &pitch_integral, &prev_pitch_error);
    float yaw_correction = computePID(target_yaw_rate, current_yaw_rate, kp_yaw, ki_yaw, kd_yaw, dt, &yaw_integral, &prev_yaw_error);

    float m1_cmd = target_thrust - roll_correction + pitch_correction - yaw_correction;
    float m2_cmd = target_thrust + roll_correction - pitch_correction - yaw_correction;
    float m3_cmd = target_thrust + roll_correction + pitch_correction + yaw_correction;
    float m4_cmd = target_thrust - roll_correction - pitch_correction + yaw_correction;

    if (target_thrust < 5.0) {
      m1_cmd = m2_cmd = m3_cmd = m4_cmd = MIN_PWM;
      roll_integral = pitch_integral = yaw_integral = 0; 
    } else {
      m1_cmd = constrain(m1_cmd, MIN_PWM, MAX_PWM);
      m2_cmd = constrain(m2_cmd, MIN_PWM, MAX_PWM);
      m3_cmd = constrain(m3_cmd, MIN_PWM, MAX_PWM);
      m4_cmd = constrain(m4_cmd, MIN_PWM, MAX_PWM);
    }

    motor1.writeMicroseconds(m1_cmd);
    motor2.writeMicroseconds(m2_cmd);
    motor3.writeMicroseconds(m3_cmd);
    motor4.writeMicroseconds(m4_cmd);
  }
}