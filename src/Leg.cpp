#include <Arduino.h>
#include "Leg.h"
#include "InverseKinematics.h"

bool Leg::legLegLifted[];

Leg::Leg(uint8_t board, uint8_t hip_pin, uint8_t thigh_pin, uint8_t knee_pin, double theta, double radius)
{
    this->board = board;
    this->hip_pin = hip_pin;
    this->thigh_pin = thigh_pin;
    this->knee_pin = knee_pin;
    this->theta = theta;
    this->radius = radius;
}

void Leg::update()
{
    Vector3_t anglesVector = calculateAngles(position);
    angles[HIP_JOINT] = anglesVector.x;
    angles[THIGH_JOINT] = anglesVector.y;
    angles[KNEE_JOINT] = anglesVector.z;
}

// ------------------- Getters -------------------

uint8_t Leg::getBoard()
{
    return board;
}

uint8_t Leg::getHipPin()
{
    return hip_pin;
}

uint8_t Leg::getThighPin()
{
    return thigh_pin;
}

uint8_t Leg::getKneePin()
{
    return knee_pin;
}

// TODO Decide if its a good idea to handle servo direction inverting here or not
int8_t Leg::getAngle(uint8_t joint)
{
    int8_t signModifier = 1;
    signModifier *= (joint == THIGH_JOINT) ? -1 : 1; // All tthigh joints are inverted
    signModifier *= (board == RIGHT_BOARD && joint!=HIP_JOINT) ? -1 : 1; // All joints on right board except hip are inverted
    return angles[joint]*signModifier;
}

Vector3_t Leg::getLegCoord()
{
    return position;
}

// ------------------- Setters -------------------

void Leg::setJointAngle(uint8_t joint, int8_t angle)
{
    angles[joint] = angle;
}

void Leg::setLegCoord(Vector3_t coord)
{
    position = coord;
}