#include <Arduino.h>
#include "GaitPlanning.h"

/**
 * @brief Construct a new Gait Planning Object
 * 
 */
GaitPlanning::GaitPlanning(ReceiverInput receiver) {

}
/**
 * @brief 
 * 
 */
void GaitPlanning::update() {
    uint64_t delta = esp_timer_get_time() - lastUpdateTime;
    if(delta >= 1000000 / UPDATE_FREQUENCY) {
        lastUpdateTime = esp_timer_get_time(); // TODO order of these lines?
        // TODO do update stuff here
    }
}

/**
 * @brief Set the Leg Velocity object
 * 
 * @param velocity 
 */
void GaitPlanning::setLegVelocity(Vector3_t velocity) {
    
}