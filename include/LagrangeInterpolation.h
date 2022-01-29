#ifndef LAGRANGE_INTERPOLATION_H
#define LAGRANGE_INTERPOLATION_H

#define NUM_POINTS 5 // Number of points to interpolate through

/**
 * Use the linked graphical demonstration to choose ALPHA and BETA values, there 
 * are sliders to change these values.
 * 
 * Graphical demonstration ==> https://www.desmos.com/calculator/t7gsylwjal
 * - A larger ALPHA value increases the initial steepness of the z-curve
 * - A larger BETA increases the height of intermediate control point 
 */
#define FUNCTION_SHAPE_ALPHA 0.7; // MUST BE IN RANGE!! [0.5, 0.77]
#define FUNCTION_SHAPE_BETA  0.35; // MUST BE IN RANGE!! [0.25, 0.5]

/**
 * @brief Usage:
 * - Create new Lagrange_5pnt oject using "Lagrange_5pnt l;"
 * - Call the set parameters function using "l.set_parameters(double max_z, double setpoint_distance)"
 * - When you want an updated Z-coordinate, call "get_z_value(double distance_to_setpoint)"
 */
class Lagrange_5pnt {
    public:
        Lagrange_5pnt();
        void set_lagrange_parameters(double max_z, double setpoint_distance);
        double get_z_value(double setpoint_distance);

    private:
        double t_pnt[5]; // Parameter L(t) where t is the distance between position and setpoint sqrt(x^2 + y^2)
        double z_pnt[5]; // z (vertical) leg position
        double param[5];
};

#endif