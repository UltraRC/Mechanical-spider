#include "accessory.h"

/**
 * @brief Adds the two passed vectors together and returns the  result
 */
Vector3_t add_vector(Vector3_t v1, Vector3_t v2)
{
    return {v1.x+v2.x, v1.y+v2.y, v1.z+v2.z};
}

/**
 * @brief Subtracts the second vector from the first and returns the result
 */
Vector3_t subtract_vector(Vector3_t v1, Vector3_t v2)
{
    return {v1.x-v2.x, v1.y-v2.y, v1.z-v2.z};
}



/**
 * @brief Convert coordinate in XYZ (body coordinates) to 
 * RTZ (Radial, tangental, vertical or XYZ in the leg frame of reference)
 * 
 * @param v1 [Vector3_t] ==> Vector to be transformed [XYZ] -> [RTZ]
 * @param phi [Degrees] ==> Angle from front of robot 
 * @return [Vector3_t ] ==> In RTZ coordinates
 */
Vector3_t XYZ_to_RTZ(Vector3_t vector, double phi)
{
    phi *= (PI/180); // Convert angle to radians
    Vector3_t return_vector = {
        vector.x*cos(phi) + vector.y*sin(phi),
        vector.y*cos(phi) - vector.x*sin(phi),
        vector.z
    };
    return return_vector;
}

/**
 * @brief Returns the 2-norm of a vector ||v||_2
 */
double vector_norm(Vector3_t v)
{
    return sqrt(v.x*v.x + v.y*v.y + v.y*v.y);
}

/**
 * @brief Scales the passed vector v by a scaler s and returns the result
 * 
 * @param v [Vector3_t] ==> Vector to be scaled
 * @param s [double] ==> Scalar
 * @return [Vector3_t] ==> Scaled vector
 */
Vector3_t vector_scale(Vector3_t v, double s)
{
    return {s*v.x, s*v.y, s*v.z};
}

/**
 * @brief Returns the 2-norm of a vector ||v||_2
 */
Vector3_t vector_normalize(Vector3_t v)
{
    double norm = vector_norm(v);
    if(norm == 0) {return {0,0,0};}
    return vector_scale(v, 1/norm);
}