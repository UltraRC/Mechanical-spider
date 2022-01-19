#ifndef GAIT_PLANNING_H
#define GAIT_PLANNING_H

#include "accessory.h"
#include "ReceiverInput.h"

#define UPDATE_FREQUENCY 100 // [Hz] TODO pick a better number for this

class GaitPlanning {
    public:
        GaitPlanning(ReceiverInput receiver);
        void update();

    private:
        void setLegVelocity(Vector3_t velocity);
        uint64_t lastUpdateTime; // Last time stamp millis()
        
        double envelope_radius; // Radius of the circle that the leg is working inside
        
        Vector3_t leg_velocity;  // [XY] (2D)

};

#endif