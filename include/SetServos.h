#ifndef SET_SERVOS_H
#define SET_SERVOS_H

#include "Leg.h"
#include "accessory.h"

#define SERVO_FREQUENCY 50 // TODO Problem: defined in two places

class SetServos {
    private:
        Vector3_t* legEndPosition;
        servoReverse_t servoReverse;
        double angleToOnTime(int8_t angle);

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