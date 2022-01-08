#ifndef ACCESSORY_H
#define ACCESSORY_H

#define SERVO_FREQUENCY 50

typedef struct {
    double x;
    double y;
    double z;
} Vector3_t;

/**
 * @brief Describes the way the motors of each servo are connected to the electrical system
 * @param board [Adafruit_PWMServoDriver] // Which board is used (left or right)
 * @param hip_pin [uint8_t] // Physical pin used to connect this servo to its respective board
 * @param thigh_pin [uint8_t]
 * @param knee_pin [uint8_t]
 */
typedef struct {
    Adafruit_PWMServoDriver board;
    uint8_t hip_pin;
    uint8_t thigh_pin;
    uint8_t knee_pin;
} servoConnection_t;

/**
 * @brief Describes the position of a leg 
 * relative to the center of the robot
 */
typedef struct {
    uint8_t angleFromFoward; // Angular position from the foward position // TODO add direction (clockwise/anticlockwise)
    uint8_t radius; // Distance from the global reference frame (center of the robot)
} legPosition_t;

/**
 * @brief Depending on where the sero is mounted and other symmetries,
 * a particular servo on a particular leg may need its direction reversed
 */
typedef struct {
    bool hipJointIsReversed;
    bool thighJointIsReversed;
    bool kneeJointIsReversed;
} servoReverse_t;

#endif // ACCESSORY_H