#ifndef NIU2X_PAINTER_RAY_TRACE_MATH_H
#define NIU2X_PAINTER_RAY_TRACE_MATH_H

#include <niu2x/math/ray.h>
#include <niu2x/painter/ray_trace/hittable.h>
#include <niu2x/painter/ray_trace/material.h>

namespace niu2x::painter::ray_trace {

using Ray = math::Ray;
using Interval = math::Interval;
using Vec3 = math::Vec3;
using Vec2 = math::Vec2;

inline Vec3 reflect(const Vec3& v, const Vec3& n)
{
    return v - 2 * dot(v, n) * n;
}

inline Vec3 refract(const Vec3& uv, const Vec3& n, double etai_over_etat)
{
    Vec3 proj_n = dot(uv, n) * n;
    Vec3 proj_t = uv - proj_n;

    Vec3 refracted_t = etai_over_etat * proj_t;
    Vec3 refracted_n = sqrt(1 - length2(refracted_t)) * normalize(proj_n);
    return refracted_t + refracted_n;
}

inline Vec3 random_unit_vec3()
{
    double theta = math::random<double>(0, 2 * math::pi);
    double phi = acos(math::random<double>(-1, 1));

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

} // namespace niu2x::painter::ray_trace

#endif