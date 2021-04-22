#include <Arduino.h>
#include <Adafruit_PWMServoDriver.h>
#include "ReceiverInput.h"

/*
- There are 6 channels comming into the receiver
- Channels 0-->5 proceed. THR:0, AIL:1, ELE:2, RUD:3, GEA:4, AUX:5
- Values will be from 500 --> 2500 uS centered on 1500 uS as the neutral position
*/

#define SERVO_FREQ 50 // Analog servos run at ~50 Hz updates

ReceiverInput ri = ReceiverInput();
Adafruit_PWMServoDriver pwmL = Adafruit_PWMServoDriver(0x40);
Adafruit_PWMServoDriver pwmR = Adafruit_PWMServoDriver(0x41);

void setup()
{
  pwmL.begin();
  pwmL.setOscillatorFrequency(27E6);
  pwmL.setPWMFreq(SERVO_FREQ);

  pwmR.begin();
  pwmR.setOscillatorFrequency(27E6);
  pwmR.setPWMFreq(SERVO_FREQ);
}

void loop()
{

  /* 
  Update receiver inputs
  */
  ri.updateReceiverValues();

  double ailAngle = (ri.getChannel(1) - 1500.0) * (9.0/100.0);
  double eleAngle = (ri.getChannel(2) - 1500.0) * (9.0/100.0);
  double rudAngle = (ri.getChannel(3) - 1500.0) * (9.0/100.0);

  double lowerLegRight = ((((ailAngle/90.0) + 1.0) + 0.5) / 20.0) * 4096.0;
  double lowerLegLeft = ((((-ailAngle/90.0) + 1.0) + 0.5) / 20.0) * 4096.0;
  
  double midLegRight = ((((eleAngle/90.0) + 1.0) + 0.5) / 20.0) * 4096.0;
  double midLegLeft = ((((-eleAngle/90.0) + 1.0) + 0.5) / 20.0) * 4096.0;

  double upperLegRight = ((((rudAngle/90.0) + 1.0) + 0.5) / 20.0) * 4096.0;
  double upperLegLeft = ((((rudAngle/90.0) + 1.0) + 0.5) / 20.0) * 4096.0;


  pwmL.setPWM(13, 0, lowerLegLeft);
  pwmL.setPWM(10, 0, lowerLegLeft);
  pwmL.setPWM(7, 0, lowerLegLeft);

  pwmR.setPWM(2, 0, lowerLegRight);
  pwmR.setPWM(5, 0, lowerLegRight);
  pwmR.setPWM(8, 0, lowerLegRight);

  pwmL.setPWM(14, 0, midLegLeft);
  pwmL.setPWM(11, 0, midLegLeft);
  pwmL.setPWM(8, 0, midLegLeft);

  pwmR.setPWM(1, 0, midLegRight);
  pwmR.setPWM(4, 0, midLegRight);
  pwmR.setPWM(7, 0, midLegRight);

  pwmL.setPWM(15, 0, upperLegLeft);
  pwmL.setPWM(12, 0, upperLegLeft);
  pwmL.setPWM(9, 0, upperLegLeft);

  pwmR.setPWM(0, 0, upperLegRight);
  pwmR.setPWM(3, 0, upperLegRight);
  pwmR.setPWM(6, 0, upperLegRight);


  
  
// ----------------------------------------------------------------------------------------------------

  // Calculate servo positions
  // Update servo positions
  

}