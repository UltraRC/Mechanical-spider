#ifndef LEG_H
#define LEG_H

#include <Adafruit_PWMServoDriver.h>
#include "SetServos.h"
#include "accessory.h"

#define NUM_LEGS 6
#define NUM_JOINTS 

#define HIP_JOINT 0
#define THIGH_JOINT 1
#define KNEE_JOINT 2

#define LEG_DISTANCE_FROM_CENTER 0 // TODO Need to set this value to the measured value

//Describes the way the motors of each servo are connected to the electrical system
typedef struct {
    Adafruit_PWMServoDriver board;
    uint8_t hip_pin;
    uint8_t thigh_pin;
    uint8_t knee_pin;
} servoConnection_t;

/**
 * @brief Describes the position of a leg 
 * relative to the center of the robot
 */
typedef struct {
    uint8_t angleFromFoward; // Angular position from the foward position // TODO add direction (clockwise/anticlockwise)
    uint8_t radius; // Distance from the global reference frame (center of the robot)
} legPosition_t;

/**
 * @brief Depending on where the sero is mounted and other symmetries,
 * a particular servo on a particular leg may need its direction reversed
 */
typedef struct {
    bool hipJointIsReversed;
    bool thighJointIsReversed;
    bool kneeJointIsReversed;
} servoReverse_t;

/**
 * @brief Leg constructor
 * @param servoConnection [servoConnection_t] // Which board and which pins each servvo is connected to
 * @param legPosition [legPosition_t] // Angle from the front position and radius
 */
class Leg {

    public:
        Leg();
        Leg(servoConnection_t servoConnection, legPosition_t legPosition, servoReverse_t servoReverse);
        //static bool legLegLifted[NUM_LEGS]; // Each leg needs to be aware of its neighbouring legs state
        void update();

    private:
        servoConnection_t servoConnectionConfig;
        legPosition_t legPosition; // Angle from front and radius
        servoReverse_t servoReverse;
        
        int8_t angles[NUM_JOINTS]; // Holds the positions for each joint angle
        Vector3_t position; // Holds the coordinates of the end of the leg relative to the coordinate of the hip joint
};

#endif //LEG_H