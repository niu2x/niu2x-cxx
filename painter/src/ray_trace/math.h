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

} // namespace niu2x::painter::ray_trace

#endif