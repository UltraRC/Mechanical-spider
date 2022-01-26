#ifndef LAGRANGE_INTERPOLATION_H
#define LAGRANGE_INTERPOLATION_H

#define NUM_POINTS 5 // Number of points to interpolate through

/**
 * 
 * Use the linked graphical demonstration to choose ALPHA and BETA values, there 
 * are sliders to change these values.
 * 
 * Graphical demonstration ==> https://www.desmos.com/calculator/t7gsylwjal
 * - A larger ALPHA value increases the initial steepness of the z-curve
 * - A larger BETA increases the height of intermediate control point 
 */
#define FUNCTION_SHAPE_ALPHA 0.6; // MUST BE IN RANGE!! [0.5, 0.77]
#define FUNCTION_SHAPE_BETA  0.4; // MUST BE IN RANGE!! [0.25, 0.5]


class Lagrange_5pnt {
    public:
        Lagrange_5pnt();
        double get_z_value(double t);

    private:
        double t_pnt[5]; // Parameter L(t) where t is the distance between position and setpoint sqrt(x^2 + y^2)
        double z_pnt[5]; // z (vertical) leg position
        double param[5];

        double x_intermediate_offset;
        double y_intermediate_offset;
        
        void set_lagrange_parameters(double max_z);

};

#endif