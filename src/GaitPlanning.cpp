#include <Arduino.h>
#include "GaitPlanning.h"

double GaitPlanning::envelope_radius = 30; // [mm] TODO Later this number should be a function of body velocity
Vector3_t GaitPlanning::leg_offset = {90,0,-30}; // [RTZ]

/**
 * @brief Construct a new Gait Planning Object
 * 
 */
GaitPlanning::GaitPlanning(ReceiverInput receiver, uint8_t legNumber, bool legLifted[6], legPosition_t legMountingPosition) { // TODO Change 6 to NUM_LEGS
    this->receiver = receiver;
    this->legNumber = legNumber;
    this->legMountingPosition = legMountingPosition;

    static uint8_t preceedingLeg = legNumber == 1 ? 6 : legNumber - 1; // Circular array inde ...4,5,6,1,2,3,4,5...
    static uint8_t proceedingLeg = legNumber == 6 ? 1 : legNumber + 1; // TODO Change 6 to NUM_LEGS

    leftNeighbourIsLifted = &legLifted[preceedingLeg];
    rightNeighbourIsLifted = &legLifted[proceedingLeg];

    leg_position = {0,0,0}; // [XYZ] ==> Position relative to leg_offset
}

void GaitPlanning::update() {
    static uint64_t lastUpdateTime;
    deltaTime = esp_timer_get_time() - lastUpdateTime;
    if(deltaTime >= 1000000 / UPDATE_FREQUENCY) {
        lastUpdateTime = esp_timer_get_time(); // TODO order of these lines?
        // TODO do stuff here
    }
}

/**
 * @brief Returns true if either neighbouring legs is lifted
 */
bool GaitPlanning::neighbourIsLifted()
{
    return *leftNeighbourIsLifted || *rightNeighbourIsLifted;
}

/**
 * Body velocity XY 2D vector [mm/s] based on the RC
 * receiver input
 */
void GaitPlanning::setBodyVelocity()
{
    bodyVelocity.x = receiver.getChannel(AIL) * MAX_BODY_VELOCTY / 1000;
    bodyVelocity.y = receiver.getChannel(ELE) * MAX_BODY_VELOCTY / 1000;
    #ifdef REVERSE_VELOCITY_X
    bodyVelocity.x *= -1;
    #endif
    #ifdef REVERSE_VELOCITY_Y
    bodyVelocity.y *= -1;
    #endif
}

/**
 * @brief Returns a vector in [RTZ] coordinates
 * Converts  leg_position from [XYZ] to [RTZ]
 * then adds it to leg_offset which is already in [RTZ].
 * Then returns that vector.
 * @return [Vector3_t] ==> Return vector 
 */
Vector3_t GaitPlanning::getPosition()
{
    return add_vector(XYZ_to_RTZ(leg_position, legMountingPosition.leg_mount_angle), leg_offset);
}