#ifndef NIU2X_PAINTER_RAY_TRACE_MATH_H
#define NIU2X_PAINTER_RAY_TRACE_MATH_H

#include <niu2x/math/ray.h>

#include "material.h"

namespace niu2x::painter::ray_trace {

using Ray = math::Ray;
using Interval = math::Interval;
using Vec3 = math::Vec3;

struct NXAPI HitRecord {
    Vec3 p;
    Vec3 normal;
    double t;
    bool front_face;
    SharedPtr<Material> material;

    void set_normal(const Vec3& ray, const Vec3& normal);
};

class NXAPI Hittable {
public:
    virtual ~Hittable() = default;
    virtual Maybe<HitRecord> hit(
        const Ray& r, const Interval& ray_interval) const = 0;
};

class NXAPI HittableGroup : public Hittable {
public:
    HittableGroup() = default;
    virtual ~HittableGroup() = default;

    void insert(SharedPtr<Hittable> ptr);

    virtual Maybe<HitRecord> hit(
        const Ray& r, const Interval& ray_interval) const override;

private:
    Vector<SharedPtr<Hittable>> objs_;
};

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
    double phi = math::random<double>(0, math::pi);

    double x = cos(theta) * sin(phi);
    double y = sin(theta) * sin(phi);
    double z = cos(phi);
    return Vec3(x, y, z);
}

} // namespace niu2x::painter::ray_trace

#endif