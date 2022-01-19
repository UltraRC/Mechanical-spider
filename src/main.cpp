#include <Arduino.h>
#include "Leg.h"
#include "LegManager.h"

#define UPDATE_FREQ 50
uint64_t lastTime = 0;

void setup()
{
    initServoControllers();
}

void loop()
{
    updateLegs();
}