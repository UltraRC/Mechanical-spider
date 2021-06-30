#include <Arduino.h>
#include <math.h>
#include "InverseKinematics.h"

// All lengths are in mm

double L1 = 47.526;
int L2 = 67.866;

double theta1 = 0; // Angle between hip reference frame and the thigh link
double theta2 = 0; // Angle between the knee reference frame and the last link

/**
 * All angle calculating functions calculateAlpha() and 
 * calculateBeta() are part of a broader calculation of
 * solving a triangle made up of the hip and shin of the robot
 * using the cosine rule
 **/
void updateAngles(double x, double y){
    double gamma = atan2(y,x);
    double alpha = calculateAlpha(x,y);
    double beta = calculateBeta(x,y);
    theta1 = gamma + alpha;
    theta2 = beta - PI;

}

double calculateAlpha(double x, double y){
    double r = sqrt(x*x + y*y);
    double numerator = L1*L1 - L2*L2 + r*r;
    double denominator = 2*L1*r;
    return acos(numerator / denominator);
}

double calculateBeta(double x, double y){
    double r = sqrt(x*x + y*y);
    double numerator = L1*L1 + L2*L2 - r*r;
    double denominator = 2*L1*L2;
    return acos(numerator / denominator);
}

/**
 * Returns an angle passed in radians as degress
 **/
double toDegrees(double angle){
    return (angle*180) / PI;
}

double getTheta1(){
    return toDegrees(theta1);
}

double getTheta2(){
    return toDegrees(theta2);
}