#ifndef NIU2X_PAINTER_RAY_TRACE_SPHERE_H
#define NIU2X_PAINTER_RAY_TRACE_SPHERE_H

#include <niu2x/math/ray.h>

namespace niu2x::painter::ray_trace {

using Vec3 = math::Vec3;

using Hittable = math::Hittable;
using HitRecord = math::HitRecord;
using Ray = math::Ray;

class Sphere : public Hittable {
public:
    Sphere(const Vec3& center, double radius);
    virtual ~Sphere() = default;

    virtual Optional<HitRecord> hit(
        const Ray& r, double min, double max) const override;

private:
    Vec3 center_;
    double radius_;
};

} // namespace niu2x::painter::ray_trace

#endif