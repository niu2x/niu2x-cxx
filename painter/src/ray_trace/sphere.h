#ifndef NIU2X_PAINTER_RAY_TRACE_SPHERE_H
#define NIU2X_PAINTER_RAY_TRACE_SPHERE_H

#include "math.h"

namespace niu2x::painter::ray_trace {

using Vec3 = math::Vec3;
using Interval = math::Interval;

using Hittable = Hittable;
using HitRecord = HitRecord;
using Ray = math::Ray;

class Sphere : public Hittable {
public:
    Sphere(const Vec3& center, double radius);
    virtual ~Sphere() = default;

    virtual Maybe<HitRecord> hit(
        const Ray& r, const Interval& ray_interval) const override;

private:
    Vec3 center_;
    double radius_;
};

} // namespace niu2x::painter::ray_trace

#endif