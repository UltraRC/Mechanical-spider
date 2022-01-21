#include <Arduino.h>
#include "GaitPlanning.h"

/**
 * @brief Construct a new Gait Planning Object
 * 
 */
GaitPlanning::GaitPlanning(ReceiverInput receiver, uint8_t legNumber, bool legLifted[6]) { // TODO Change 6 to NUM_LEGS
    this->receiver = receiver;
    this->legNumber = legNumber;

    static uint8_t preceedingLeg = legNumber == 1 ? 6 : legNumber - 1; // 
    static uint8_t proceedingLeg = legNumber == 6 ? 1 : legNumber + 1;

    leftNeighbourIsLifted = &legLifted[preceedingLeg];
    rightNeighbourIsLifted = &legLifted[proceedingLeg];
}

/**
 * @brief 
 * 
 */
void GaitPlanning::update() {
    static uint64_t lastUpdateTime;
    delta = esp_timer_get_time() - lastUpdateTime;
    if(delta >= 1000000 / UPDATE_FREQUENCY) {
        lastUpdateTime = esp_timer_get_time(); // TODO order of these lines?
        // TODO do update stuff here
    }
}

/**
 * @brief Returns true if either immediately neighbouring legs are lifted
 * 
 * @return true 
 * @return false 
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
 * @brief Set the Leg Velocity object
 * 
 * @param velocity 
 */
void GaitPlanning::setLegVelocity(Vector3_t velocity) {
    
}

/**
 * Interface (public methods) ==> What information needs to be given and taken from other classes?
 * Stuff other classes can ACCESS / get methods:
 * - set current XYZ set position
 * 
 * Stuff this class needs to know from other classes ==> Constructor arguments / set methods:
 * - Needs to no ITSELF which leg THIS is
 * - Needs to know the state (swing/stance) and (later) position of other legs
 * 
 * Is there anything that is common to all instances of this class? ==> Static members:
 * - Envelope radius
 * - Body velocity ==> Need to convert receiver signals into body velocity
 */