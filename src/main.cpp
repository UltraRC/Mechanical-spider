#include <Arduino.h>
#include "SetServos.h"
#include "ReceiverInput.h"

/*
- There are 6 channels comming into the receiver
- Channels 0-->5 proceed. THR:0, AIL:1, ELE:2, RUD:3, GEA:4, AUX:5
- Values will be from 500 --> 2500 uS centered on 1500 uS as the neutral position
*/

ReceiverInput receiver; // Collects input from receiver

void setup()
{
  receiver = ReceiverInput(false); // false meaning return receiver values as uS instead of servo degrees
  Serial.begin(9600);
}

void loop()
{
  receiver.updateReceiverValues();
  receiver.printReceiverValues();
  //Serial.println(receiver.getChannel(0));
}
