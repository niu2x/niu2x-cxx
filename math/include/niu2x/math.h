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
inline constexpr double infinity = std::numeric_limits<double>::infinity();
inline constexpr double pi = 3.1415926535897932385;

inline double deg2rad(double degrees) { return degrees * pi / 180.0; }

NXAPI Color to_color(const Vec3& v);

} // namespace niu2x::math

#endif
