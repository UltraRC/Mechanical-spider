#include <Arduino.h>
#include "LegManager.h"
#include "Leg.h"
#include "ReceiverInput.h"

#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver leftBoard = Adafruit_PWMServoDriver(LEFT_BOARD_ADDRESS);
Adafruit_PWMServoDriver rightBoard = Adafruit_PWMServoDriver(RIGHT_BOARD_ADDRESS);

// ----------------- Construct a group of legs with their associated data -----------------

// Information for the connection of each leg
servoConnection_t legConnection1 = {leftBoard , 0, 1, 2};
servoConnection_t legConnection2 = {leftBoard , 3, 4, 5};
servoConnection_t legConnection3 = {leftBoard , 6, 7, 8};
servoConnection_t legConnection4 = {rightBoard, 0, 1, 2};
servoConnection_t legConnection5 = {rightBoard, 3, 4, 5};
servoConnection_t legConnection6 = {rightBoard, 6, 7, 8};

// Information for the position of each leg
// {Angle, radius, hip*, thigh*, knee*} *offset angles
// TODO make sure that offsets deflect joints in the correct direction
legPosition_t legPosition1 = {120, RADIUS,  3, -5,  0};
legPosition_t legPosition2 = {180, RADIUS, -1, -7,  3};
legPosition_t legPosition3 = {240, RADIUS, -1, -5, -2};
legPosition_t legPosition4 = {300, RADIUS, -3,  6, -5};
legPosition_t legPosition5 = {0  , RADIUS,  5,  2, -6}; 
legPosition_t legPosition6 = {60 , RADIUS, -2, -6, -6};

// Information on the direction of each servo in each leg
// A state of true means the servo is reversed
// Order of joints is {hipJointIsReversed, thighJointIsReversed, KneeJointIsReversed}
servoReverse_t servoReverse1 = {false, true , false};
servoReverse_t servoReverse2 = {false, true , false};
servoReverse_t servoReverse3 = {false, true , false};
servoReverse_t servoReverse4 = {false, false, true };
servoReverse_t servoReverse5 = {false, false, true };
servoReverse_t servoReverse6 = {false, false, true };

Leg legs[NUM_LEGS] = {
    Leg(legConnection1, legPosition1, servoReverse1),
    Leg(legConnection2, legPosition2, servoReverse2),
    Leg(legConnection3, legPosition3, servoReverse3),
    Leg(legConnection4, legPosition4, servoReverse4),
    Leg(legConnection5, legPosition5, servoReverse5),
    Leg(legConnection6, legPosition6, servoReverse6)
};

// ----------------- ----------------- ----------------- -----------------v

/**
 * @brief Initializes the PCA9685 PWM servo controller boards
 */
void initServoControllers()
{
    leftBoard.begin();
    rightBoard.begin();

    leftBoard.setPWMFreq(SERVO_FREQUENCY);
    rightBoard.setPWMFreq(SERVO_FREQUENCY);

    //delay(10); // TODO Maybe necessary
}

/**
 * @brief Sends an update tick to each leg 
 */
void updateLegs()
{
    for(size_t i=0; i<NUM_LEGS; i++) {
        legs[i].update();
    }
}