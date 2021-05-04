/*
Aims if this class:
- Take in angles for each joint and set the corresponding servo to that value.
- Calibrate each joint so that it actually is where it is set

Possible/future features:
- Disable motors
- Set motors to a storage state

*/

/*
- Leg numbering

  1             4
   \  _______  /
    \/       \/
2---|         |---5
    |         |
    /\_______/\
   /           \
  3             6

  - Joint numbering is 1 for upper hip, 2 for lower hip and 3 for knee
  - Rotations towards the front for the upper hip joints are considered possitive
  - Rotations upwards of the remaining lower hip and knee joints are considered possitive

*/

#include <Arduino.h>
#include "SetServos.h"
#include <Adafruit_PWMServoDriver.h>

#define SERVO_FREQUENCY 50 // Analog servos run at 50 Hz
#define OSCILATOR_FREQUENCY 27E6 // 27 MHz clock frequency

const int NUMBER_OF_LEGS = 6;
const int NUMBER_OF_JOINTS = 3;

/*
- There are two pwm servo controllers with 0x40 and 0x41 as addresses for the respective left and right driver boards
*/
Adafruit_PWMServoDriver leftMotors = Adafruit_PWMServoDriver(0x40);
Adafruit_PWMServoDriver rightMotors = Adafruit_PWMServoDriver(0x41);

/*
- The timing number sent to the setPwm() function is PW * SERVO_FREQUENCY * 4096 where PW is pulse with in milli seconds
- 1.5 ms is the center servo position, 0.5 ms is the min, and 2.5 is the max
*/

double jointPulseWidth [6][3]; // Holds the pulse widths for each servo in ms * 4096 ==> A proportion of 4096
double jointAngles [6][3]; // Holds the angle positions for each from [-90, 90]
const double jointOffsetAngles [6][3] = {{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0}}; // Holds the calibration or offset angle of each joint

SetServos::SetServos(){
    initializeServoValues();
    
    leftMotors.begin();
    rightMotors.begin();

    leftMotors.setOscillatorFrequency(OSCILATOR_FREQUENCY);
    rightMotors.setOscillatorFrequency(OSCILATOR_FREQUENCY);

    leftMotors.setPWMFreq(SERVO_FREQUENCY);
    rightMotors.setPWMFreq(SERVO_FREQUENCY);
}

/*
Set all default positions to 90 degrees
*/
static void initializeServoValues(){
  for(int leg=0;leg<6;leg++){
      for(int joint=0;joint<3;joint++){
        jointAngles[leg][joint] = 90;
      }
    }
}

void SetServos::update(){
  calculateJointPulseWidth(); //Given an angle, calculte its pulse width for each joint taking into account the sign conventions
  setAngles(); //Set the servos to their calculated pulse width
}

/*
All left leg angles are inverted due to the orrientation of the servo motors
*/
void calculateJointPulseWidth(){
  for(int leg=0;leg<NUMBER_OF_LEGS/2;leg++){ // Left legs
    for(int joint=0;joint<NUMBER_OF_JOINTS;joint++){
      double angle = -1 * jointAngles[leg][joint] - jointOffsetAngles[leg][joint];
      jointPulseWidth[leg][joint] = angleToTime(angle);
    }
  }

  for(int leg=NUMBER_OF_LEGS/2;leg<NUMBER_OF_LEGS;leg++){ // Left legs
    for(int joint=0;joint<=NUMBER_OF_JOINTS-1;joint++){
      double angle = jointAngles[leg][joint] + jointOffsetAngles[leg][joint];
      jointPulseWidth[leg][joint] = angleToTime(angle);
    }
  }
}

/*
Maps argument angle = [-90,90] to pulseWidth = [0.5,2.5] * 4096
*/
static double angleToTime(double angle){
  double pulseWidth = (angle + 90.0) * (2.0/180.0) + 0.5;
  pulseWidth *= 4096.0/20.0;
  return pulseWidth;
}

/*
- Sets the angle for each servo motor
*/
static void setAngles(){
  for(int leg=0;leg<NUMBER_OF_LEGS/2;leg++){
    for(int joint=0;joint<NUMBER_OF_JOINTS-1;joint++){
      int pin = 3*leg + joint + 7; // First joint of first leg is attached to pin 7 and ascends from there
      leftMotors.setPWM(pin,0,jointPulseWidth[leg][joint]);
    }
  }

  for(int leg = NUMBER_OF_LEGS/2;leg<NUMBER_OF_LEGS;leg++){
    for(int joint=0;joint<NUMBER_OF_JOINTS;joint++){
      int pin = 8 - 3*leg - joint; // First joint of first leg is attached to pin 8 and descends from there
      leftMotors.setPWM(pin,0,jointPulseWidth[leg][joint]);
    }
  }
}