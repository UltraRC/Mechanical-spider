#include <Arduino.h>
#include <Adafruit_PWMServoDriver.h>
#include "ReceiverInput.h"
#include "SetServos.h"

/*
- There are 6 channels comming into the receiver
- Channels 0-->5 proceed. THR:0, AIL:1, ELE:2, RUD:3, GEA:4, AUX:5
- Values will be from 500 --> 2500 uS centered on 1500 uS as the neutral position
*/

#define SERVO_FREQ 50 // Analog servos run at ~50 Hz updates

//ReceiverInput ri = ReceiverInput();
SetServos motors = SetServos();

void setup()
{

}

void loop()
{

  motors.update();
  /*
  ri.updateReceiverValues(); // Update receiver inputs

  double ailAngle = (ri.getChannel(1) - 1500.0) * (9.0/100.0);
  double eleAngle = (ri.getChannel(2) - 1500.0) * (9.0/100.0);
  double rudAngle = (ri.getChannel(3) - 1500.0) * (9.0/100.0);

  double lowerLegRight = ((((ailAngle/90.0) + 1.0) + 0.5) / 20.0) * 4096.0;
  double lowerLegLeft = ((((-ailAngle/90.0) + 1.0) + 0.5) / 20.0) * 4096.0;
  
  double midLegRight = ((((eleAngle/90.0) + 1.0) + 0.5) / 20.0) * 4096.0;
  double midLegLeft = ((((-eleAngle/90.0) + 1.0) + 0.5) / 20.0) * 4096.0;

  double upperLegRight = ((((rudAngle/90.0) + 1.0) + 0.5) / 20.0) * 4096.0;
  double upperLegLeft = ((((rudAngle/90.0) + 1.0) + 0.5) / 20.0) * 4096.0;
  */



  
  
// ----------------------------------------------------------------------------------------------------

  // Calculate servo positions
  // Update servo positions
  

}