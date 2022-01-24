#ifndef LAGRANGE_INTERPOLATION_H
#define LAGRANGE_INTERPOLATION_H

#define NUM_POINTS 5 // Number of points to interpolate through

class Lagrange_5pnt {
    public:
        Lagrange_5pnt();

    private:
        double t[5]; // Parameter L(t) where t is the distance between position and setpoint sqrt(x^2 + y^2)
        double z[5]; // z (vertical) leg position

        double x_intermediate_offset;
        double y_intermediate_offset;
        
        void set_lagrange_parameters();

};

#endif