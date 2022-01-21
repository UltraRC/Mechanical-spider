#ifndef GAIT_PLANNING_H
#define GAIT_PLANNING_H

#include "accessory.h"
#include "ReceiverInput.h"

// Reverse the direction of movement of the robot
//#define REVERSE_VELOCITY_X
//#define REVERSE_VELOCITY_Y

#define DEFAULT_X_POS 0
#define DEFAULT_Y_POS 0
#define DEFAULT_Z_POS 0

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

    static double envelope_radius; // Radius of the circle that the leg is working inside
    static ReceiverInput receiver;
    static Vector3_t bodyVelocity; // Is based apon receiver inputs

    public:
        GaitPlanning(ReceiverInput receiver, uint8_t legNumber, bool legLifted[6], legPosition_t legMountingPosition); // TODO Change 6 to NUM_LEGS
        void update();
        Vector3_t getPosition();

    private:
        uint64_t deltaTime; // Ammount of time passed since last tick

        Vector3_t DEFAULT_LEG_POSITION; // In the reference from of the leg. E.g x is the tangent direction y is radial and z is up
        legPosition_t legMountingPosition;
        uint8_t legNumber; // Which leg (of six) is THIS one
        Vector3_t legPosition; // Absolute leg position
        Vector3_t legOffset;  // Leg position relative to DEFAULT_LEG_POSITION
        Vector3_t legVelocity;  // [XY] (2D)
        bool* leftNeighbourIsLifted;
        bool* rightNeighbourIsLifted;

        void bodyToLegVelocity();
        void setLegVelocity(Vector3_t velocity);
        void setBodyVelocity();
        void calculateLegPosition(); 
        bool neighbourIsLifted();
        void setDefaultLegPosition();
        Vector3_t add(Vector3_t v1, Vector3_t v2);

};

#endif