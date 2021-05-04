#ifndef SET_SERVOS_H
#define SET_SERVOS_H

class SetServos {

    public:
    SetServos();
    void update();

    private:


};

void calculateJointPulseWidth();
void setAngles();
static void initializeServoValues();
static double angleToTime(double angle);

#endif