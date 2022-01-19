#include <Arduino.h>
#include "Leg.h"
#include "SetServos.h"
#include "InverseKinematics.h"

uint8_t Leg::legCount = 1; // Legs are numbered 1-6
Leg::gaitPlanning = GaitPlanning(receiver); //  TODO move receiver as static vairable in leg and fix object initilisation

Leg::Leg(servoConnection_t servoConnection, legPosition_t legPosition, servoReverse_t servoReverse, ReceiverInput receiver)
{
    legNumber = legCount; // Identifies which leg 1-6 this leg is
    this->servoConnectionConfig = servoConnection;
    this->legPosition = legPosition; // Angle and distance of leg mounting positions
    this->servoReverse = servoReverse;
    this-> receiver = receiver;
    defaultPosition = {80,0,-60};
    setServos = SetServos(&angles, servoConnectionConfig, servoReverse);

    legCount += 1; // Adds one leg to the list
}

void Leg::update()
{
    int32_t x = -1*receiver.getChannel(AIL)/10;
    int32_t y =    receiver.getChannel(ELE)/10;

    double theta = toRadians(legPosition.angleFromFoward);

    int32_t x_prime = x*cos(theta) + y*sin(theta);
    int32_t y_prime = y*cos(theta) - x*sin(theta);

    position.x = defaultPosition.x - x_prime;
    position.y = defaultPosition.y - y_prime;
    position.z = defaultPosition.z - receiver.getChannel(THR)/10;

    angles = calculateAngles(position);

    angles.x += legPosition.offset_angle_hip;
    angles.y += legPosition.offset_angle_thigh;
    angles.z += legPosition.offset_angle_knee;

    gaitPlanning.update();
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
 * What information does a Leg object contain?
 * - Stores information on how the servos are connected to the other electronics
 * - Stores information on the mounting location of this leg relative to the robots frame
 * - Stores information on the angle of each joing and the position of the leg in 3D space
 * 
 * What needs to bee done with this information?
 * - Convert leg position information into joint angle information (inverse kinematics)
 * - Set the position of each of the legs servos to the angle stored
 */