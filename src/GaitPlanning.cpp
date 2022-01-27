#include <Arduino.h>
#include "GaitPlanning.h"

double GaitPlanning::envelope_radius = 26; // [mm] TODO Later this number should be a function of body velocity
Vector3_t GaitPlanning::leg_offset = {STANCE_RADIUS, 0, STANCE_Z_OFFSET}; // [RTZ]
Vector3_t GaitPlanning::body_velocity = {0,0,0};

/**
 * @brief Construct a new Gait Planning Object
 * 
 */
GaitPlanning::GaitPlanning(ReceiverInput* receiver, uint8_t legNumber, bool legLifted[6], legPosition_t legMountingPosition) { // TODO Change 6 to NUM_LEGS
    this->receiver = receiver;
    this->legNumber = legNumber;
    this->legMountingPosition = legMountingPosition;

    uint8_t preceedingLeg = legNumber == 1 ? 6 : legNumber - 1; // Circular array inde ...4,5,6,1,2,3,4,5...
    uint8_t proceedingLeg = legNumber == 6 ? 1 : legNumber + 1; // TODO Change 6 to NUM_LEGS

    leftNeighbourIsLifted = &legLifted[preceedingLeg-1]; // TODO check indicies
    rightNeighbourIsLifted = &legLifted[proceedingLeg-1];
    lifted = &legLifted[legNumber-1];

    leg_position = {0,0,0}; // [XYZ] Initilize position ==> Position relative to leg_offset
    state = stance;
}

void GaitPlanning::update() {
    static uint64_t lastUpdateTime;
    deltaTime = esp_timer_get_time() - lastUpdateTime;
    dt = deltaTime / 1000000.0;
    if(deltaTime >= 1000000.0 / UPDATE_FREQUENCY) {
        lastUpdateTime = esp_timer_get_time(); // TODO order of these lines? esp_timer_get_time()
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
            state = stance;
            break;
        }

    }
}

void GaitPlanning::stanceMovementUpdate()
{
    leg_position.x -= body_velocity.x; // TODO delta time may be very small
    leg_position.y -= body_velocity.y;
    leg_position.z = 0;

    if(legOutsideEnvelope() && !neighbourIsLifted()) { //TODO there are other conditions to change state e.g Neighbour lifted
        calculateSwingParameters();
        state = swing;
        *lifted = true;
    }
}

/**
 * @brief Calculates the 3D position to swing to
 * 
 */
void GaitPlanning::calculateSwingParameters()
{
    // TODO if body_velocity < *x* then move to {0,0,0}
    target_swing_position = vector_normalize(body_velocity);
    target_swing_position = vector_scale(target_swing_position, envelope_radius);

    double distance_to_setpoint = vector_norm(subtract_vector(target_swing_position, leg_position));

    lagrange.set_lagrange_parameters(STEP_HEIGHT, distance_to_setpoint);
}

/**
 * @brief 
 * 
 */
void GaitPlanning::swingMovementUpdate()
{
    Vector3_t displacement = {0,0,0}; // Vector that points in the direction of target_position with size velocity*dt
    double distance_to_setpoint = vector_norm(subtract_vector(target_swing_position, leg_position));

    displacement.x = target_swing_position.x - leg_position.x; // Find direction to move in
    displacement.y = target_swing_position.y - leg_position.y;

    displacement = vector_normalize(displacement); // Normalize direction ==> ||v||_2 = 1
    displacement = vector_scale(displacement, SWING_VELOCITY); // TODO *deltaTime Scale by a distance/time * time value ==> step distance

    if(vector_norm(displacement) >= distance_to_setpoint) { // If step size is larger than distance to set point, move straight to the setpoint and change to stance
        leg_position = target_swing_position;
        state = stance;
        *lifted = false;
        return;
    }

    Vector3_t setVector = add_vector(leg_position, displacement); // Move leg_position by one unit of distance in the direction of displacement
    //setVector.z = STEP_HEIGHT; // [mm] // Old method
    setVector.z = lagrange.get_z_value(distance_to_setpoint); // New method

    leg_position = setVector;
}

/**
 * @brief Returns true if either neighbouring legs is lifted
 */
bool GaitPlanning::neighbourIsLifted()
{
    return (*leftNeighbourIsLifted || *rightNeighbourIsLifted);
}

bool GaitPlanning::legOutsideEnvelope()
{
    return vector_norm(leg_position) > envelope_radius + HYSTERESIS_ENVELOPE_RADIUS;
}

/**
 * Body velocity XY 2D vector [mm/s] based on the RC
 * receiver input
 */
void GaitPlanning::setBodyVelocity()
{
    body_velocity.x = receiver->getChannel(AIL) * MAX_BODY_VELOCTY / 1000.0; // TODO converting integerround off error?
    body_velocity.y = receiver->getChannel(ELE) * MAX_BODY_VELOCTY / 1000.0;
    body_velocity.z = receiver->getChannel(RUD) * MAX_BODY_VELOCTY / 1000.0; // Yaw
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