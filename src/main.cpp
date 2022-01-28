#include <Arduino.h>
#include "LegManager.h"

void setup()
{
    //Serial.begin(9600);
    initServoControllers();
}

void loop()
{
    updateLegs();
}