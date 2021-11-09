#ifndef LEG_H
#define LEG_H

#define NUM_LEGS 6
#define NUM_JOINTS 

#define HIP_JOINT 0
#define THIGH_JOINT 1
#define KNEE_JOINT 2

#define LEFT_BOARD 1
#define RIGHT_BOARD 2

#define LEG_DISTANCE_FROM_CENTER 0 // TODO Need to set this value to the measured value

typedef struct {
    double x;
    double y;
    double z;
} Vector3_t;

/**
 * @param board [uint8_t]
 * @param hip_pin [uint8_t]
 * @param thigh_pin [uint8_t]
 * @param knee_pin [uint8_t]
 * @param theta [double] Angular position from the foward position
 * @param radius [double] Distance from the global reference frame (center of the robot)
 */
class Leg {

    public:
        Leg();
        Leg(uint8_t board, uint8_t hip_pin, uint8_t thigh_pin, uint8_t knee_pin, double theta, double radius);
        static bool legLegLifted[NUM_LEGS]; // Each leg needs to be aware of its neighbouring legs state
        
        /**
         * 
         */
        void update();

        /**
         * @breif Returns which servo controller board is associated with this leg
         * @return board [uint8_t] ==> 1 is left, 2 is right. USE MACRO LEFT_BOARD and RIGHT_BOARD
         */
        uint8_t getBoard();

        /**
         * @returns [uint8_t] the servocontroller pin number associated with this joint
         */
        uint8_t getHipPin();

        /**
         * @returns [uint8_t] the servocontroller pin number associated with this joint
         */
        uint8_t getThighPin();

        /**
         * @returns [uint8_t] the servocontroller pin number associated with this joint
         */
        uint8_t getKneePin();

        /**
         * @returns [int8_t] The current angle set for a particular joint within this leg
         */
        int8_t getAngle(uint8_t joint);
        
        /**
         * Sets a the specified joint to the passed angle parameter for this leg
         * @param joint [uint8_t] One of KNEE_JOINT, THIGH_JOINT, or HIP_JOINT macros
         * @param angle [int8_t] Angle in the range [-90, 90]
         */
        void setJointAngle(uint8_t joint, int8_t angle);

        /**
         * Gets the current position of the leg
         * @returns [Vector3_t] The current set position of the leg end
         */
        Vector3_t getLegCoord();

        /**
         * Sets the leg to a new coordinate
         * @param coord [Vector3_t] is the new set position of the leg end
         */
        void setLegCoord(Vector3_t coord);

    private:
        double theta; // Angular position from the foward position
        double radius; // Distance from the global reference frame (center of the robot)
        uint8_t board;
        uint8_t hip_pin;
        uint8_t thigh_pin;
        uint8_t knee_pin;
        int8_t angles[NUM_JOINTS]; // Holds the positions for each joint angle
        Vector3_t position; // Holds the coordinates of the end of the leg relative to the first leg joint
};

#endif //LEG_H