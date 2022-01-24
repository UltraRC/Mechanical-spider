#include "LagrangeInterpolation.h"

/**
 * @brief This class is for creating a smooth Z coordinate path for
 * the leg to follow during its "swing phase". It is based on a Lagrange interpolation
 * method to create a path between five points.
 * - Graphical demonstration ==> https://www.desmos.com/calculator/h4iplk85sa
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

void Lagrange_5pnt::set_lagrange_parameters()
{

}