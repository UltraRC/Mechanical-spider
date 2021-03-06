#include <Arduino.h>
#include "Leg.h"
#include "SetServos.h"
#include "InverseKinematics.h"
#include "GaitPlanning.h"

uint8_t Leg::legCount = 1; // Legs are numbered 1-6
bool Leg::legLifted[NUM_LEGS];
ReceiverInput* Leg::receiver = new ReceiverInput();

Leg::Leg(servoConnection_t servoConnection, legPosition_t legPosition, servoReverse_t servoReverse)
{
    legNumber = legCount; // Identifies which leg 1-6 this leg is
    this->servoConnectionConfig = servoConnection;
    this->legPosition = legPosition; // Angle and distance of leg mounting positions
    this->servoReverse = servoReverse;
    setServos = SetServos(&angles, servoConnectionConfig, servoReverse);
    gaitPlanning = new GaitPlanning(receiver, legNumber, legLifted, legPosition);
    legCount += 1; // Adds one leg to the list
}

void Leg::update()
{
    /* TODO move to gaitPlanning.cpp
    position.x = defaultPosition.x - legVelocity.x;
    position.y = defaultPosition.y - legVelocity.y;
    position.z = defaultPosition.z - receiver->getChannel(THR)/10;
    */

    // TODO move this to setServos.cpp tbh
    receiver->update();
    gaitPlanning->update();
    position = gaitPlanning->getPosition();
    //Serial.printf("Leg#%u ==> {%f,%f,%f}\n",legNumber, position.x, position.y, position.z);
    if(legNumber==6) {
        //Serial.printf("-----------------------\n");
    }
    angles = calculateAngles(position);

    angles.x += legPosition.offset_angle_hip; // TODO use add_vector
    angles.y += legPosition.offset_angle_thigh;
    angles.z += legPosition.offset_angle_knee;

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