#include <Arduino.h>
#include "Leg.h"
#include "LegManager.h"

#define UPDATE_FREQ 50

LegManager lm;

uint64_t lastTime = 0;

void setup()
{
    lm = LegManager();
    Serial.begin(9600);
}

void loop()
{
    uint64_t delta = esp_timer_get_time() - lastTime;

    if(delta >= 1000000 / UPDATE_FREQ) {
        lastTime = esp_timer_get_time();
        lm.update();
        //Serial.printf("Delta: %ld\n", delta);
    }
}