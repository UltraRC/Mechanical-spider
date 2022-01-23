#include <Arduino.h>
#include "GaitPlanning.h"

double GaitPlanning::envelope_radius = 30; // [mm] TODO Later this number should be a function of body velocity
Vector3_t GaitPlanning::leg_offset = {90,0,-50}; // [RTZ]
Vector3_t GaitPlanning::body_velocity = {0,0,0};

/**
 * @brief Construct a new Gait Planning Object
 * 
 */
GaitPlanning::GaitPlanning(ReceiverInput* receiver, uint8_t legNumber, bool legLifted[6], legPosition_t legMountingPosition) { // TODO Change 6 to NUM_LEGS
    this->receiver = receiver;
    this->legNumber = legNumber;
    this->legMountingPosition = legMountingPosition;

    static uint8_t preceedingLeg = legNumber == 1 ? 6 : legNumber - 1; // Circular array inde ...4,5,6,1,2,3,4,5...
    static uint8_t proceedingLeg = legNumber == 6 ? 1 : legNumber + 1; // TODO Change 6 to NUM_LEGS

    leftNeighbourIsLifted = &legLifted[preceedingLeg];
    rightNeighbourIsLifted = &legLifted[proceedingLeg];

    leg_position = {0,0,0}; // [XYZ] Initilize position ==> Position relative to leg_offset
    state = stance;
}

void GaitPlanning::update() {
    static uint64_t lastUpdateTime;
    deltaTime = esp_timer_get_time() - lastUpdateTime;
    if(deltaTime >= 1000000 / UPDATE_FREQUENCY) {
        lastUpdateTime = esp_timer_get_time(); // TODO order of these lines?
        
        setBodyVelocity();

        switch (state)
        {
        case stance:
            stanceMovementUpdate();
            break;

        case swing:
            swingMovementUpdate();
            break;
        
        default:
            break;
        }

    }
}

void GaitPlanning::stanceMovementUpdate()
{
    leg_position.x -= body_velocity.x;
    leg_position.y -= body_velocity.y;
    leg_position.z = 0;

    if(legOutsideEnvelope()) {state = swing;} //TODO there are other conditions to change state e.g Neighbour lifted
}

/**
 * @brief 
 * 
 */
void GaitPlanning::swingMovementUpdate()
{
    double swing_height = 10; // [mm] ==> The height of the inflection point

    Vector3_t starting_point = {0,0,0};
    Vector3_t inflection_point = {0,0,leg_offset.z + swing_height};
    Vector3_t end_point = {0,0,0};

    Vector3_t direction = subtract_vector(inflection_point, leg_position);
    direction = vector_normalize(direction);

}

/**
 * @brief Returns true if either neighbouring legs is lifted
 */
bool GaitPlanning::neighbourIsLifted()
{
    return *leftNeighbourIsLifted || *rightNeighbourIsLifted;
}

bool GaitPlanning::legOutsideEnvelope()
{
    return vector_norm(leg_position) >= envelope_radius;
}

/**
 * Body velocity XY 2D vector [mm/s] based on the RC
 * receiver input
 */
void GaitPlanning::setBodyVelocity()
{
    body_velocity.x = receiver->getChannel(AIL) * MAX_BODY_VELOCTY / 1000; // TODO converting integerround off error?
    body_velocity.y = receiver->getChannel(ELE) * MAX_BODY_VELOCTY / 1000;
    #ifdef REVERSE_VELOCITY_X
    body_velocity.x *= -1;
    #endif
    #ifdef REVERSE_VELOCITY_Y
    body_velocity.y *= -1;
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