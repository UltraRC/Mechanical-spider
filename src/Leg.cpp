#include <Arduino.h>
#include "Leg.h"
#include "SetServos.h"

//bool Leg::legLegLifted[];

SetServos setServos;

Leg::Leg(servoConnection_t servoConnection, legPosition_t legPosition, servoReverse_t servoReverse)
{
    this->servoConnectionConfig = servoConnection;
    this->legPosition = legPosition;
    this->servoReverse = servoReverse;

    setServos = SetServos(&position, servoConnectionConfig, servoReverse);
}

void Leg::update()
{
    setServos.updateServoPositions();
}

/**
 * What information does a Leg object contain?
 * - Stores information on how the servos are connected to the other electronics
 * - Stores information on the mounting location of this leg relative to the robots frame
 * - Stores information on the angle of each joing and the position of the leg in 3D space
 * 
 * What needs to bee done with this information?
 * - Convert leg position information into joint angle information (inverse kinematics)
 * - Set the position of each of the legs servos to the angle stored
 * - 
 */