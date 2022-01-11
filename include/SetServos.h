#ifndef SET_SERVOS_H
#define SET_SERVOS_H

#include "accessory.h"

class SetServos {
    private:
        Vector3_t* angles;
        servoReverse_t servoReverse;
        uint16_t angleToOnTime(int8_t angle, bool reverse);

        Adafruit_PWMServoDriver board;
        uint8_t hip_pin;
        uint8_t thigh_pin;
        uint8_t knee_pin;

    public:
        SetServos();
        SetServos(Vector3_t* legEndPosition, servoConnection_t servoConnectionConfig, servoReverse_t servoReverse);
        void updateServoPositions();
};

#endif //SET_SERVOS_H