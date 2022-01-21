#ifndef GAIT_PLANNING_H
#define GAIT_PLANNING_H

#include "accessory.h"
#include "ReceiverInput.h"

// Reverse the direction of movement of the robot
//#define REVERSE_VELOCITY_X
//#define REVERSE_VELOCITY_Y

// Set the velocities for different stages of the gait cycle
#define SWING_VELOCITY 100 // [mm/s] TODO this will later be variable depending on body velocity
#define MAX_BODY_VELOCTY 10 // [mm/s]

#define UPDATE_FREQUENCY 100 // [Hz] TODO pick a better number for this


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
        GaitPlanning(ReceiverInput receiver, uint8_t legNumber, bool legLifted[6]); // TODO Change 6 to NUM_LEGS
        void update();
        Vector3_t getPosition();

    private:
        void setLegVelocity(Vector3_t velocity);
        uint64_t delta;
        uint8_t legNumber;

        bool* leftNeighbourIsLifted;
        bool* rightNeighbourIsLifted;
        
        motion_state_t legState; // 
        static double envelope_radius; // Radius of the circle that the leg is working inside
        
        Vector3_t leg_velocity;  // [XY] (2D)
        static Vector3_t bodyVelocity; // Is based apon receiver inputs
        void setBodyVelocity();
        bool neighbourIsLifted();

        static ReceiverInput receiver;

};

#endif