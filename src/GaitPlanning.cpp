#include <Arduino.h>
#include "GaitPlanning.h"

double GaitPlanning::envelope_radius = 30; // [mm] TODO Later this number should be a function of body velocity

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

    setDefaultLegPosition();
}

/**
 * @brief 
 * 
 */
void GaitPlanning::update() {
    static uint64_t lastUpdateTime;
    deltaTime = esp_timer_get_time() - lastUpdateTime;
    if(deltaTime >= 1000000 / UPDATE_FREQUENCY) {
        lastUpdateTime = esp_timer_get_time(); // TODO order of these lines?
        // TODO do update stuff here
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
 * @brief Transorms the XY vector of body velocity into
 * an XY vector of leg velocity based on the angle the leg makes with the body
 * 
 * // TODO may need to change some signs here
 */
void GaitPlanning::bodyToLegVelocity()
{
    double x = -1*receiver.getChannel(AIL)/10;
    double y =    receiver.getChannel(ELE)/10;
    double theta = PI / 180  * legMountingPosition.angleFromFoward; // Convert to radians
    legVelocity.x = x*cos(theta) + y*sin(theta);
    legVelocity.y = y*cos(theta) - x*sin(theta);
}

void GaitPlanning::calculateLegPosition()
{
    legPosition = add(DEFAULT_LEG_POSITION, legOffset);
}

void GaitPlanning::setDefaultLegPosition()
{
    double angleFromFront = PI/180 * legMountingPosition.angleFromFoward;
    DEFAULT_LEG_POSITION = // {tangental, radial, vertical} => From the legs perscpective
    {
        DEFAULT_X_POS*cos(angleFromFront) + DEFAULT_Y_POS*sin(angleFromFront),
        DEFAULT_Y_POS*cos(angleFromFront) - DEFAULT_X_POS*sin(angleFromFront),
        DEFAULT_Z_POS
    }; 
}

Vector3_t GaitPlanning::add(Vector3_t v1, Vector3_t v2)
{
    return {v1.x+v2.x, v1.y+v2.y, v1.z+v2.z};
}

Vector3_t GaitPlanning::getPosition()
{
    return legPosition;
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