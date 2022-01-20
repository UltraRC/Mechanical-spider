#include <Arduino.h>
#include "Leg.h"
#include "SetServos.h"
#include "InverseKinematics.h"

uint8_t Leg::legCount = 1; // Legs are numbered 1-6

Leg::Leg(servoConnection_t servoConnection, legPosition_t legPosition, servoReverse_t servoReverse)
{
    legNumber = legCount; // Identifies which leg 1-6 this leg is
    this->servoConnectionConfig = servoConnection;
    this->legPosition = legPosition; // Angle and distance of leg mounting positions
    this->servoReverse = servoReverse;
    this-> receiver = receiver;
    defaultPosition = {80,0,-60};
    setServos = SetServos(&angles, servoConnectionConfig, servoReverse);
    receiver = new ReceiverInput();
    gaitPlanning = new GaitPlanning(*receiver);
    legCount += 1; // Adds one leg to the list
}

void Leg::update()
{
    receiver->update();

    position.x = defaultPosition.x - legVelocity.x;
    position.y = defaultPosition.y - legVelocity.y;
    position.z = defaultPosition.z - receiver->getChannel(THR)/10;

    angles = calculateAngles(position);

    angles.x += legPosition.offset_angle_hip;
    angles.y += legPosition.offset_angle_thigh;
    angles.z += legPosition.offset_angle_knee;

    gaitPlanning->update();
    setServos.updateServoPositions();
}

/**
 * @brief Stores the xyz cooordinate position of the leg end relative to the hip joint
 * @param x [int32_t]
 * @param y [int32_t]
 * @param z [int32_t]
 */
void Leg::setPosition(int32_t x, int32_t y, int32_t z)
{
    position.x = x;
    position.y = y;
    position.z = z;
}


/**
 * @brief Transorms the XY vector of body velocity into
 * an XY vector of leg velocity based on the angle the leg makes with the body
 * 
 * // TODO may need to change some signs here
 */
void Leg::bodyToLegVelocity()
{
    double x = -1*receiver->getChannel(AIL)/10;
    double y =    receiver->getChannel(ELE)/10;
    double theta = toRadians(legPosition.angleFromFoward);
    legVelocity.x = x*cos(theta) + y*sin(theta);
    legVelocity.y = y*cos(theta) - x*sin(theta);y*cos(theta) - x*sin(theta);
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
 */