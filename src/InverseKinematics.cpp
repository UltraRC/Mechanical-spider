#include <Arduino.h>
#include <math.h>
#include "InverseKinematics.h"

/**
 * Inverse kinematics - https://www.instructables.com/DIY-Arduino-Quadruped-Robot-With-Inverse-Kinematic/
 **/
// All lengths are in mm

double L1 = 38.750; // Middle of hp joint
double L2 = 47.526; // Thigh
double L3 = 67.866; // Shin

double theta1 = 0; // Angle between body and thigh in xy plane
double theta2 = 0; // Angle between hip-link and thigh in the zx plane
double theta3 = 0; // Angle of the knee joint in the zx plane

/**
 * All angle calculating functions calculateAlpha() and 
 * calculateBeta() are part of a broader calculation of
 * solving a triangle made up of the hip and shin of the robot
 * using the cosine rule
 **/
void updateAngles(double x, double y, double z){
    theta1 = atan2(y,x);
    double D = sqrt(x*x + y*y);
    double d = D - L1;
    double R = sqrt(d*d + z*z);
    double gamma = atan2(z,d);
    double alpha = calculateAlpha(R);
    double beta = calculateBeta(R);
    theta2 = gamma + alpha;
    theta3 = beta - PI;
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

//---------------------------------------------------------

double getTheta1(){
    return toDegrees(theta1);
}

double getTheta2(){
    return toDegrees(theta2);
}

double getTheta3(){
    return toDegrees(theta3);
}