/*
Aims of this file:
- Take in angles for each joint and set the corresponding servo to that value.
- Calibrate each joint so that it actually is where it is set

Possible/future features:
- Disable motors

Leg numbering:

  1             4
   \  _______  /
    \/       \/
2---|         |---5
    |         |
    /\_______/\
   /           \
  3             6

  - Joint numbering is 1 for upper hip, 2 for lower hip and 3 for knee
  - Clockwise rotations of the hip joint are considered possitive
  - Rotations upwards of the remaining lower hip and knee joints are considered possitive
*/

/*
- There are 6 channels comming into the receiver
- Channels 0-->5 proceed. THR:0, AIL:1, ELE:2, RUD:3, GEA:4, AUX:5
- Values will be from 500 --> 2500 uS centered on 1500 uS as the neutral position
*/

#include <Adafruit_PWMServoDriver.h>
#include <Arduino.h>
#include "SetServos.h"
#include <math.h>

#define SERVO_FREQUENCY 50 // Analog servos run at 50 Hz

//const int LEGS_SIZE = 6;
//const int JOINTS_SIZE = 3;

const int leftMotorPortStart = 0;
const int leftMotorPortEnd = 8;
const int rightMotorPortStart = 15;
const int rightMotorPortEnd = 7;

const int LEGS_SIZE = 6;
const int JOINTS_SIZE = 3;

/*
- There are two pwm servo controllers with 0x40 and 0x41 as addresses for the respective left and right driver boards
*/
Adafruit_PWMServoDriver leftMotors;
Adafruit_PWMServoDriver rightMotors;

double jointPulseWidth [LEGS_SIZE][JOINTS_SIZE]; // Holds the pulse widths for each servo in ms * 4096 ==> A proportion of 4096
double jointAngles [LEGS_SIZE][JOINTS_SIZE]; // Holds the angle positions for each from [-90, 90]
const double jointOffsetAngles [LEGS_SIZE][JOINTS_SIZE] = {{6,5,0},{0,5,0},{9,-3,0},{10,0,20},{6,-3,0},{0,5,10}}; // Hip is possitive for anti-clockwise, thigh is negative for upwards, knee is possitive for upwards, rightMotors are reversed for thigh and knee

/*
Constructor:
- Initialises the two PCA9685 chips
*/
void servoInitialize(){

  leftMotors = Adafruit_PWMServoDriver(0x40);
  rightMotors = Adafruit_PWMServoDriver(0x41);
    
  leftMotors.begin();
  rightMotors.begin();

  leftMotors.setPWMFreq(SERVO_FREQUENCY);
  rightMotors.setPWMFreq(SERVO_FREQUENCY);
}

void servoUpdate(){
  setServos();
}

double angleToOnTime(int leg, int joint){
  int angle = jointAngles[leg][joint] + jointOffsetAngles[leg][joint];
  double onTime = map(angle, -90, 90, 500, 2500) / 20000.0; // 20,000 uS is the period of the PWM signal
  return onTime;
}

void setServos(){
  for(int leg=0;leg<LEGS_SIZE;leg++){
    for(int joint=0;joint<JOINTS_SIZE;joint++){
      int pin = 3*leg + joint;
      if(leg>2){ // Right motors
        pin = map(pin,8,16,rightMotorPortStart,rightMotorPortEnd);
        int pwm = angleToOnTime(leg, joint) * 4095;
        rightMotors.setPWM(pin,0,pwm);
      }
      else{
        pin = map(pin,0,8,leftMotorPortStart,leftMotorPortEnd);
        int pwm = angleToOnTime(leg, joint) * 4095;
        leftMotors.setPWM(pin,0,pwm);
      }
    }
  }
}

/**
 * - Sets the angle for a particular joint on a particular leg
 * - Due to the geometry and physical arrangement of the servo
 * motors on the robot, some of the angle signs need to be reversed,
 * hence the use of the signModifer variable.
 **/
void setAngle(int leg, int joint, double angle){
  int signModifier = 0;
  if(leg >=1 || leg <=6 || joint >=1 || joint <=3){
    if(leg>=4)signModifier++;
    if(joint==2)signModifier++;
    jointAngles[leg-1][joint-1] = pow(-1,signModifier)*(angle + 90*(int)(joint==3));
  }
}