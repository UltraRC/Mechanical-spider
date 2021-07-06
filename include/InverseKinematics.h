#ifndef INVERSE_KINEMATICS_H
#define INVERSE_KINEMATICS_H

void updateAngles(double x, double y, double z);
double calculateAlpha(double R);
double calculateBeta(double R);
double toDegrees(double angle);
double getTheta1();
double getTheta2();
double getTheta3();
#endif