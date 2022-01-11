#ifndef INVERSE_KINEMATICS_H
#define INVERSE_KINEMATICS_H

#include "Leg.h"

Vector3_t calculateAngles(Vector3_t position);
double calculateAlpha(double R);
double calculateBeta(double R);
double toDegrees(double angle);
double toRadians(double angle);
#endif