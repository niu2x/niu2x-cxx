#ifndef NIU2X_MATH_H
#define NIU2X_MATH_H

#include <limits>
#include <niu2x/math/linalg_alias.h>
#include <niu2x/math/ray.h>

namespace niu2x::math {

template <class T>
T clamp(const T& n, const T& min, const T& max)
{
    if (n < min)
        return min;
    if (n > max)
        return max;
    return n;
}

NXAPI double hit_sphere(const Vec3& center, double radius, const Ray& r);

inline constexpr double max_double = std::numeric_limits<double>::max();

} // namespace niu2x::math

#endif
