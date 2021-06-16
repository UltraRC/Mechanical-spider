#ifndef SET_SERVOS_H
#define SET_SERVOS_H

class SetServos {

    public:
        SetServos();
        void update();

    private:
        void calculateJointPulseWidth();
        void setAngles();
        double angleToTime(double);
        void initializeServoValues();

};

#endif