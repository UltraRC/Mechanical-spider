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
    /*
    uint64_t delta = esp_timer_get_time() - lastTime;
    if(delta >= 1000000 / UPDATE_FREQ) {
        lastTime = esp_timer_get_time();
    }
    */
   
    updateLegs();
}