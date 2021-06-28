#ifndef SET_SERVOS_H
#define SET_SERVOS_H

void servoInitialize();
void setServos();
double angleToOnTime(int leg, int joint);
void servoUpdate();


#endif