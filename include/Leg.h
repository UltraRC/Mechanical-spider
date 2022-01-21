#ifndef LEG_H
#define LEG_H

#include <Adafruit_PWMServoDriver.h>
#include "accessory.h"
#include "SetServos.h"
#include "ReceiverInput.h"
#include "GaitPlanning.h"

#define NUM_LEGS 6
#define NUM_JOINTS 

#define HIP_JOINT 0
#define THIGH_JOINT 1
#define KNEE_JOINT 2

#define LEG_DISTANCE_FROM_CENTER 80 // [mm] measured by hand

/**
 * @brief Leg constructor
 * @param servoConnection [servoConnection_t] // Which board and which pins each servvo is connected to
 * @param legPosition [legPosition_t] // Angle from the front position and radius
 */
class Leg {

    ReceiverInput* receiver;
    GaitPlanning* gaitPlanning; // Object used to plan how each leg moves

    public:
        Leg();
        Leg(servoConnection_t servoConnection, legPosition_t legPosition, servoReverse_t servoReverse);
        //static bool legLegLifted[NUM_LEGS]; // Each leg needs to be aware of its neighbouring legs state
        void update();
        void setPosition(int32_t x, int32_t y, int32_t z); // TODO Temporary REMOVE!!!

    private:
        static uint8_t legCount;
        uint8_t legNumber;
        static bool legLifted[NUM_LEGS];  // Legs need to know if their neighbouring leg is lifted
        servoConnection_t servoConnectionConfig;
        legPosition_t legPosition; // Angle from front and radius
        servoReverse_t servoReverse;
        SetServos setServos;
        
        Vector3_t defaultPosition; // [XYZ] Holds the default position coordinates of the end of the leg relative to the coordinate of the hip joint
        Vector3_t position; // [XYZ] Holds the absolute position of the leg end from the hip [mm]
        Vector3_t angles; // [HIP, THIGH, KNEE] // Holds the positions for each joint angle

        Vector3_t legVelocity;

        void bodyToLegVelocity();
};

#endif //LEG_H