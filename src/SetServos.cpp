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
#include <Wire.h>
#include "SetServos.h"

//const int LEGS_SIZE = 6;
//const int JOINTS_SIZE = 3;

//const int LEGS_SIZE = 6;
//const int JOINTS_SIZE = 3;

bool servosEnabled = true;

/*
- There are two pwm servo controllers with 0x40 and 0x41 as addresses for the respective left and right driver boards
*/
Adafruit_PWMServoDriver leftBoard;
Adafruit_PWMServoDriver rightBoard;

/*
Constructor:
- Initialises the two PCA9685 chips
*/
void servoInitialize(){
  leftBoard = Adafruit_PWMServoDriver(LEFT_BOARD_ADDRESS);
  rightBoard = Adafruit_PWMServoDriver(RIGHT_BOARD_ADDRESS);
  
  leftBoard.begin();
  leftBoard.setPWMFreq(SERVO_FREQUENCY);
  
  rightBoard.begin();
  rightBoard.setPWMFreq(SERVO_FREQUENCY);
}

double angleToOnTime(int8_t angle){
  int32_t onTime = map(angle, -90, 90, 500, 2500); // 20,000 uS is the period of the PWM signal
  onTime = constrain(onTime, 500, 2500);
  return onTime * 4096 * SERVO_FREQUENCY * 0.000001;
}

void updateServos(Leg* legs)
{
  if(servosEnabled) {
    leftBoard.wakeup();
    rightBoard.wakeup();
  } else {
    leftBoard.sleep();
    rightBoard.sleep();
  }

  for(uint i=0; i<NUM_LEGS; i++) {
        int8_t hipAngle = legs[i].getAngle(HIP_JOINT);
        int8_t thighAngle = legs[i].getAngle(THIGH_JOINT);
        int8_t kneeAngle = legs[i].getAngle(KNEE_JOINT);
        if(legs[i].getBoard() == LEFT_BOARD) {
            leftBoard.setPin(legs[i].getHipPin(), angleToOnTime(hipAngle));
            leftBoard.setPin(legs[i].getThighPin(), angleToOnTime(thighAngle));
            leftBoard.setPin(legs[i].getKneePin(), angleToOnTime(kneeAngle));
        }

        if(legs[i].getBoard() == RIGHT_BOARD) {
            rightBoard.setPin(legs[i].getHipPin(), angleToOnTime(hipAngle));
            rightBoard.setPin(legs[i].getThighPin(), angleToOnTime(thighAngle));
            rightBoard.setPin(legs[i].getKneePin(), angleToOnTime(kneeAngle));
        }
    }
}

void enableServos()
{
  servosEnabled = true;
}

void disableServos()
{
  servosEnabled = false;
}