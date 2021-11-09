#include <Arduino.h>
#include "LegManager.h"
#include "Leg.h"
#include "SetServos.h"

Leg legs[NUM_LEGS] = {
    Leg(LEFT_BOARD, 0, 1, 2, 0.0, 0.0),
    Leg(LEFT_BOARD, 3, 4, 5, 0.0, 0.0),
    Leg(LEFT_BOARD, 6, 7, 8, 0.0, 0.0),
    Leg(RIGHT_BOARD, 9, 8, 7, 0.0, 0.0),
    Leg(RIGHT_BOARD, 12, 11, 10, 0.0, 0.0),
    Leg(RIGHT_BOARD, 15, 14, 13, 0.0, 0.0)
};

Vector3_t setPosition = {100,0,0};

LegManager::LegManager()
{
    servoInitialize();
}

void LegManager::update()
{
    for(int8_t z = -40; z<40; z++) {
        
        setPosition.z = z;

        for(uint8_t i=0; i<NUM_LEGS; i++) {
            legs[i].setLegCoord(setPosition);
        }
        
        updateLegs();
        updateServos(legs);
    }

    for(int8_t z = 40; z>-40; z--) {
        
        setPosition.z = z;

        for(uint8_t i=0; i<NUM_LEGS; i++) {
            legs[i].setLegCoord(setPosition);
        }
        
        updateLegs();
        updateServos(legs);
    }
}

void LegManager::updateLegs()
{
    for(uint8_t i=0; i<NUM_LEGS; i++) {
        legs[i].update();
    }
}