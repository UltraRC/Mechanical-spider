#ifndef GAIT_PLANNING_H
#define GAIT_PLANNING_H

#include "accessory.h"
#include "ReceiverInput.h"
#include "LagrangeInterpolation.h"

// Reverse the direction of movement of the robot
#define REVERSE_VELOCITY_X
//#define REVERSE_VELOCITY_Y

#define HYSTERESIS_ENVELOPE_RADIUS 5 // TODO Set this to avoid leg from swinging as soon as it lands

// Set the velocities for different stages of the gait cycle
#define SWING_VELOCITY 27.0 // [mm/s] TODO this will later be variable depending on body velocity
#define MAX_BODY_VELOCTY 50.0 // [mm/s]

#define UPDATE_FREQUENCY 100.0 // [Hz] TODO pick a better number for this

#define STANCE_RADIUS 95 // [mm] ==> Radial distance from hip joint
#define STANCE_Z_OFFSET -60 // [mm] ==> Z-Offset from hip joint

#define STEP_HEIGHT 23 // [mm] ==> The max height that the leg reaches during swing state

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
    static Vector3_t body_velocity; // Is based apon receiver inputs
    static Vector3_t leg_offset; // In the reference from of the leg. E.g x is the radial direction y is tangent and z is up

    public:
        GaitPlanning(ReceiverInput* receiver, uint8_t legNumber, bool legLifted[6], legPosition_t legMountingPosition); // TODO Change 6 to NUM_LEGS
        void update();
        Vector3_t getPosition();

    private:
        uint64_t deltaTime; // [uS] Ammount of time passed since last tick
        double dt; // [S]
        ReceiverInput* receiver;
        Lagrange_5pnt lagrange;

        legPosition_t legMountingPosition;
        uint8_t legNumber; // Which leg (of six) is THIS one
        Vector3_t leg_position; // Leg position relative to leg_offset in [XYZ] ==> Body coordinates
        Vector3_t legVelocity;  // [XY] (2D)
        bool* leftNeighbourIsLifted;
        bool* rightNeighbourIsLifted;
        bool* lifted;
        
        motion_state_t state;
        Vector3_t target_swing_position;
        void calculateSwingParameters();

        void setBodyVelocity();
        bool neighbourIsLifted();

        void stanceMovementUpdate();
        void swingMovementUpdate();
        bool legOutsideEnvelope();
};

#endif