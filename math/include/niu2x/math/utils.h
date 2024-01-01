#ifndef NIU2X_MATH_UTILS_H
#define NIU2X_MATH_UTILS_H

#include <random>
#include <niu2x/api.h>
#include <niu2x/color.h>
#include <niu2x/math/linalg_alias.h>
#include <niu2x/math/constant.h>

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
constexpr T clamp(const T& n, const T& min, const T& max)
{
    if (n < min)
        return min;
    if (n > max)
        return max;
    return n;
}

inline double deg2rad(double degrees) { return degrees * pi / 180.0; }

inline double random()
{
    thread_local std::uniform_real_distribution<double> distribution(0.0, 1.0);
    thread_local std::mt19937 generator;
    return distribution(generator);
}

inline Vec3 random_vec3()
{
    return normalize(Vec3(random(), random(), random()));
}

template <class T>
inline T random(const T& min, const T& max)
{
    return static_cast<T>(random() * (max - min) + min);
}

inline Vec3 random_unit_vec3()
{
    double theta = math::random<double>(0, 2 * math::pi);
    double phi = math::random<double>(0, math::pi);

    double x = cos(theta) * sin(phi);
    double y = sin(theta) * sin(phi);
    double z = cos(phi);
    return Vec3(x, y, z);
}

inline Vec2 random_unit_vec2()
{
    double theta = math::random<double>(0, 2 * math::pi);
    double x = cos(theta);
    double y = sin(theta);
    return Vec2(x, y);
}

template <class T>
inline T sign(const T& n)
{
    return n > 0 ? 1 : (n < 0 ? -1 : 0);
}

} // namespace niu2x::math

#endif