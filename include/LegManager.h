#ifndef LEG_MANAGER_H
#define LEG_MANAGER

#define LEFT_BOARD_ADDRESS 0x40
#define RIGHT_BOARD_ADDRESS 0x41

void initServoControllers();

void updateLegs();

#endif