#include "LagrangeInterpolation.h"

/**
 * @brief This class is for creating a smooth Z coordinate path for
 * the leg to follow during its "swing phase". It is based on a Lagrange interpolation
 * method to create a path between five points.
 * - Graphical demonstration ==> https://www.desmos.com/calculator/t7gsylwjal
 * - Mathmatical reference ==> https://brilliant.org/wiki/lagrange-interpolation/#:~:text=The%20Lagrange%20interpolation%20formula%20is,point%20(1%2C3).
 * The method of finding a Z leg path that this class is replacing is shown graphically
 * here ==> https://www.desmos.com/calculator/dqawljke0c
 */

/**
 * @brief Construct a new Lagrange_5pnt::Lagrange_5pnt object
 * 
 */
Lagrange_5pnt::Lagrange_5pnt()
{
    
}

void Lagrange_5pnt::set_lagrange_parameters(double max_z)
{
    double alpha = FUNCTION_SHAPE_ALPHA;
    double beta =  FUNCTION_SHAPE_BETA;

    z_pnt[0] = 0;
    z_pnt[2] = max_z; 
    double z_offset = beta * (z_pnt[2] - z_pnt[0]);
    
    t_pnt[4] = 0; // *t_max?*

    t_pnt[0] = 0;
    t_pnt[2] = (t_pnt[0]+t_pnt[4]) / 2;
    double t_offset = alpha * (t_pnt[2] - t_pnt[0]);
    
    t_pnt[1] = t_pnt[2] - t_offset;
    t_pnt[3] = t_pnt[2] + t_offset;

    z_pnt[1] = z_pnt[2] - z_offset;
    z_pnt[3] = z_pnt[1];
    z_pnt[4] = z_pnt[0];

    param[0] = z_pnt[0] / (t_pnt[0]-t_pnt[1])*(t_pnt[0]-t_pnt[2])*(t_pnt[0]-t_pnt[3])*(t_pnt[0]-t_pnt[4]);
    param[1] = z_pnt[1] / (t_pnt[1]-t_pnt[0])*(t_pnt[1]-t_pnt[2])*(t_pnt[1]-t_pnt[3])*(t_pnt[1]-t_pnt[4]);    
    param[2] = z_pnt[2] / (t_pnt[2]-t_pnt[0])*(t_pnt[2]-t_pnt[1])*(t_pnt[2]-t_pnt[3])*(t_pnt[2]-t_pnt[4]);    
    param[3] = z_pnt[3] / (t_pnt[3]-t_pnt[0])*(t_pnt[3]-t_pnt[1])*(t_pnt[3]-t_pnt[2])*(t_pnt[3]-t_pnt[4]);
    param[4] = z_pnt[4] / (t_pnt[4]-t_pnt[0])*(t_pnt[4]-t_pnt[1])*(t_pnt[4]-t_pnt[2])*(t_pnt[4]-t_pnt[3]);
}

double Lagrange_5pnt::get_z_value(double t)
{
    double return_value =
    (t-t_pnt[1])*(t-t_pnt[2])*(t-t_pnt[3])*(t-t_pnt[4]) * param[0] +
    (t-t_pnt[0])*(t-t_pnt[2])*(t-t_pnt[3])*(t-t_pnt[4]) * param[0] +
    (t-t_pnt[0])*(t-t_pnt[1])*(t-t_pnt[3])*(t-t_pnt[4]) * param[0] +
    (t-t_pnt[0])*(t-t_pnt[1])*(t-t_pnt[2])*(t-t_pnt[4]) * param[0] +
    (t-t_pnt[0])*(t-t_pnt[1])*(t-t_pnt[2])*(t-t_pnt[3]) * param[0];

    return return_value;
}