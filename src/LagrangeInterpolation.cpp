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
 * Usage:
 * - Create new Lagrange_5pnt oject using "Lagrange_5pnt l;"
 * - Call the set parameters function using "l.set_parameters(double max_z, double setpoint_distance)"
 * - When you want an updated Z-coordinate, call "get_z_value(double distance_to_setpoint)"
 */

/**
 * @brief Construct a new Lagrange_5pnt::Lagrange_5pnt object
 */
Lagrange_5pnt::Lagrange_5pnt()
{
        
}

/**
 * @brief Sets the basic parameters and sets the control points/nodes
 * 
 * @param max_z [double] ==> The maximum height the leg z-path should reach
 * @param setpoint_distance [double] ==> Distance between the start-point and end point in the XY plane
 */
void Lagrange_5pnt::set_lagrange_parameters(double max_z, double setpoint_distance)
{
    // A larger alpha value increases the initial steepness of the z-curve
    // A larger beta increases the height of intermediate control point 

    double alpha = FUNCTION_SHAPE_ALPHA;
    double beta =  FUNCTION_SHAPE_BETA;

    // Each z_pnt[] component is a z-coordinate that the path goes through
    //  With corrresponding t_pnt[] components with dimmension [distance to endpoint(XY-plane)] or target_position(XY-plane) - current_position(XY-plane)
    z_pnt[0] = 0;
    z_pnt[2] = max_z; 
    double z_offset = beta * (z_pnt[2] - z_pnt[0]);
    
    t_pnt[4] = setpoint_distance;

    t_pnt[0] = 0;
    t_pnt[2] = (t_pnt[0]+t_pnt[4]) / 2;
    double t_offset = alpha * (t_pnt[2] - t_pnt[0]);
    
    t_pnt[1] = t_pnt[2] - t_offset;
    t_pnt[3] = t_pnt[2] + t_offset;

    z_pnt[1] = z_pnt[2] - z_offset;
    z_pnt[3] = z_pnt[1];
    z_pnt[4] = z_pnt[0];

    // From desmos example, each param[] component is y_* / denominator
    param[0] = z_pnt[0] / (t_pnt[0]-t_pnt[1])*(t_pnt[0]-t_pnt[2])*(t_pnt[0]-t_pnt[3])*(t_pnt[0]-t_pnt[4]);
    param[1] = z_pnt[1] / (t_pnt[1]-t_pnt[0])*(t_pnt[1]-t_pnt[2])*(t_pnt[1]-t_pnt[3])*(t_pnt[1]-t_pnt[4]);    
    param[2] = z_pnt[2] / (t_pnt[2]-t_pnt[0])*(t_pnt[2]-t_pnt[1])*(t_pnt[2]-t_pnt[3])*(t_pnt[2]-t_pnt[4]);    
    param[3] = z_pnt[3] / (t_pnt[3]-t_pnt[0])*(t_pnt[3]-t_pnt[1])*(t_pnt[3]-t_pnt[2])*(t_pnt[3]-t_pnt[4]);
    param[4] = z_pnt[4] / (t_pnt[4]-t_pnt[0])*(t_pnt[4]-t_pnt[1])*(t_pnt[4]-t_pnt[2])*(t_pnt[4]-t_pnt[3]);
}

/**
 * @brief Returns the z-value for the leg during its swing phase
 * 
 * @param setpoint_distance [double] ==> Distance to the setpoint (e.g. pass set_point-current_position)
 * @return  [double] ==> Z-value for the leg during its swing phase
 */
double Lagrange_5pnt::get_z_value(double setpoint_distance)
{
    double z_value =
    (setpoint_distance-t_pnt[1])*(setpoint_distance-t_pnt[2])*(setpoint_distance-t_pnt[3])*(setpoint_distance-t_pnt[4]) * param[0] +
    (setpoint_distance-t_pnt[0])*(setpoint_distance-t_pnt[2])*(setpoint_distance-t_pnt[3])*(setpoint_distance-t_pnt[4]) * param[1] +
    (setpoint_distance-t_pnt[0])*(setpoint_distance-t_pnt[1])*(setpoint_distance-t_pnt[3])*(setpoint_distance-t_pnt[4]) * param[2] +
    (setpoint_distance-t_pnt[0])*(setpoint_distance-t_pnt[1])*(setpoint_distance-t_pnt[2])*(setpoint_distance-t_pnt[4]) * param[3] +
    (setpoint_distance-t_pnt[0])*(setpoint_distance-t_pnt[1])*(setpoint_distance-t_pnt[2])*(setpoint_distance-t_pnt[3]) * param[4];

    return z_value;
}