#ifndef INVERSE_KINEMATICS_H
#define INVERSE_KINEMATICS_H

void updateAngles(double x, double y);
double calculateAlpha(double x, double y);
double calculateBeta(double x, double y);
double toDegrees(double angle);
double getTheta1();
double getTheta2();
#endif