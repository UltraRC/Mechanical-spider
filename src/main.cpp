#include <Arduino.h>
#include "SetServos.h"
#include "ReceiverInput.h"

/*
- There are 6 channels comming into the receiver
- Channels 0-->5 proceed. THR:0, AIL:1, ELE:2, RUD:3, GEA:4, AUX:5
- Values will be from 500 --> 2500 uS centered on 1500 uS as the neutral position
*/

void setup()
{
  Serial.begin(9600);
  servoInitialize();
}

void loop()
{
  servoUpdate();
}