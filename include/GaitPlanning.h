#ifndef GAIT_PLANNING_H
#define GAIT_PLANNING_H

#include "accessory.h"
#include "ReceiverInput.h"

#define UPDATE_FREQUENCY 100 // [Hz] TODO pick a better number for this

#define SWING_VELOCITY 100 // [mm/s] TODO this will later be variable depending on body velocity

#define STANCE_RADIUS 20 // [mm] ==> Radial distance from hip joint
#define STANCE_Z_OFFSET 0 // [mm] ==> Z-Offset from hip joint

/**
 * @brief The leg can be in one of three states not_moving, stance (on the ground propelling the robot)
 * and swing (leg moving from one location to another).
 * (TODO or maybe "not_moving" should be part of stance)
 */
typedef enum {
    not_moving = 0,
    stance,
    swing
} motion_state_t;

class GaitPlanning {
    public:
        GaitPlanning(ReceiverInput receiver);
        void update();
        Vector3_t getPosition();

    private:
        void setLegVelocity(Vector3_t velocity);
        uint64_t delta;
        
        motion_state_t legState; // 
        double envelope_radius; // Radius of the circle that the leg is working inside
        
        Vector3_t leg_velocity;  // [XY] (2D)

};

#endif