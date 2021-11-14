/*
Aims of this file:
- Take in angles for each joint and set the corresponding servo to that value.
- Calibrate each joint so that it actually is where it is set

Leg numbering:

  1             6 
   \  _______  /
    \/       \/
2---|         |---5
    |         |
    /\_______/\
   /           \
  3             4

  - Joint numbering is 0 for upper hip, 1 for lower hip and 2 for knee
  - Anti-clockwise rotations of the hip joint are considered possitive
  - Rotations upwards of the remaining lower hip and knee joints are considered possitive
*/

#include <Arduino.h>
#include <Adafruit_PWMServoDriver.h>
#include "SetServos.h"

SetServos::SetServos(Vector3_t* legEndPosition, servoConnection_t servoConnectionConfig, servoReverse_t servoReverse)
{
  this->legEndPosition = legEndPosition;
  this->board = servoConnectionConfig.board;
  this->hip_pin = servoConnectionConfig.hip_pin;
  this->knee_pin = servoConnectionConfig.knee_pin;
  this->knee_pin = servoConnectionConfig.knee_pin;
  this->servoReverse = servoReverse;
}

/**
 * @param angle [int8_t] Takes an angle in the range [-90,90], and
 * returns an integer number calculated by ratio: time / (4096 * update_period) 
 * which represents the duty cycle percentage, but as a proportion
 */
double SetServos::angleToOnTime(int8_t angle){
  int32_t onTime = map(angle, -90, 90, 500, 2500); // 20,000 uS is the period of the PWM signal
  onTime = constrain(onTime, 500, 2500);
  return onTime * 4096 * SERVO_FREQUENCY * 0.000001;
}

void SetServos::updateServoPositions()
{
  board.setPin(hip_pin, angleToOnTime(legEndPosition->x), servoReverse.hipJointIsReversed);
  board.setPin(thigh_pin, angleToOnTime(legEndPosition->y), servoReverse.thighJointIsReversed);
  board.setPin(knee_pin, angleToOnTime(legEndPosition->z), servoReverse.kneeJointIsReversed);
}