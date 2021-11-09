#include <Arduino.h>
#include <math.h>
#include "InverseKinematics.h"
#include "Leg.h"

/**
 * Inverse kinematics - https://www.instructables.com/DIY-Arduino-Quadruped-Robot-With-Inverse-Kinematic/
 **/
// All lengths are in mm

double L1 = 38.750; // Middle of hip joint
double L2 = 47.526; // Thigh
double L3 = 67.866; // Shin

/**
 * All angle calculating functions calculateAlpha() and 
 * calculateBeta() are part of a broader calculation of
 * solving a triangle made up of the hip and shin of the robot
 * using the cosine rule
 **/
Vector3_t calculateAngles(Vector3_t position)
{
    double theta1 = 0; // Angle between body and thigh in xy plane
    double theta2 = 0; // Angle between hip-link and thigh in the zx plane
    double theta3 = 0; // Angle of the knee joint in the zx plane

    theta1 = atan2(position.y,position.x);
    double D = sqrt(position.x*position.x + position.y*position.y);
    double d = D - L1;
    double R = sqrt(d*d + position.z*position.z);
    double gamma = atan2(position.z,d);
    double alpha = calculateAlpha(R);
    double beta = calculateBeta(R);
    theta2 = gamma + alpha;
    theta3 = beta - PI;

    theta1 = toDegrees(theta1);
    theta2 = toDegrees(theta2);
    theta3 = toDegrees(theta3);

    //Serial.printf("T1: %f, T2: %f, T3: %f\n", theta1, theta2, theta3); // TODO remove this code if not needed

    Vector3_t angles = {theta1, theta2, theta3+90}; // TODO put this +90 degrees somewhere else, maybe an array of offset angles
    return angles;
}

double calculateAlpha(double R){
    double numerator = L2*L2 - L3*L3 + R*R;
    double denominator = 2*L2*R;
    return acos(numerator / denominator);
}

double calculateBeta(double R){
    double numerator = L2*L2 + L3*L3 - R*R;
    double denominator = 2*L2*L3;
    return acos(numerator / denominator);
}

/**
 * Returns an angle passed in radians as degress
 **/
double toDegrees(double angle){
    return (angle*180) / PI;
}