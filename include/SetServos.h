#ifndef SET_SERVOS_H
#define SET_SERVOS_H

#include "Leg.h"

#define LEFT_BOARD_ADDRESS 0x40
#define RIGHT_BOARD_ADDRESS 0x41
#define LEFT_BOARD 1
#define RIGHT_BOARD 2

#define SERVO_FREQUENCY 50 // Analog servos run at 50 Hz

void servoInitialize();

/**
 * @param angle [int8_t] Takes an angle in the range [-90,90], and
 * returns an integer number calculated by ratio: time / (4096 * update_period) 
 * which represents the duty cycle percentage, but as a proportion
 */
double angleToOnTime(int8_t angle);

/**
 * @param legs [Leg*] A pointer to an array of legs
 * This function takes angle values stored in each Leg object
 * and sets the corresponding joint servo to that angle
 */
void updateServos(Leg* legs);

/**
 * Wakes up both servo controller boards
 */
void enableServos();

/**
 * Makes both servo controller boards sleep
 */
void disableServos();

#endif //SET_SERVOS_H