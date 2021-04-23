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

*/

#include <Arduino.h>
#include "SetServos.h"
#include <Adafruit_PWMServoDriver.h>

#define SERVO_FREQUENCY 50 // Analog servos run at 50 Hz
#define OSCILATOR_FREQUENCY 27E6 // 27 MHz clock frequency

/*
- There are two pwm servo controllers with 0x40 and 0x41 as addresses for the respective left and right driver boards
*/
Adafruit_PWMServoDriver leftMotors = Adafruit_PWMServoDriver(0x40);
Adafruit_PWMServoDriver rightMotors = Adafruit_PWMServoDriver(0x41);

SetServos::SetServos(){
    
    leftMotors.begin();
    rightMotors.begin();

    leftMotors.setOscillatorFrequency(OSCILATOR_FREQUENCY);
    rightMotors.setOscillatorFrequency(OSCILATOR_FREQUENCY);

    leftMotors.setPWMFreq(SERVO_FREQUENCY);
    rightMotors.setPWMFreq(SERVO_FREQUENCY);

}