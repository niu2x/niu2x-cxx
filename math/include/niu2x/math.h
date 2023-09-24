#ifndef NIU2X_MATH_H
#define NIU2X_MATH_H

#include <niu2x/math/linalg_alias.h>
#include <niu2x/math/constant.h>
#include <niu2x/math/ray.h>
#include <niu2x/math/interval.h>
#include <niu2x/math/size.h>

/**
 * @brief       math utils
 */
namespace niu2x::math {

/**
 * @brief       clamp a value in [min, max]
 * @param       n     the value to be clamped
 * @param       min   lower bound
 * @param       max   upper bound
 * @return      clampd value */
template <class T>
T clamp(const T& n, const T& min, const T& max)
{
    if (n < min)
        return min;
    if (n > max)
        return max;
    return n;
}

inline double deg2rad(double degrees) { return degrees * pi / 180.0; }

NXAPI Color to_color(const Vec3& v);

} // namespace niu2x::math

#endif
