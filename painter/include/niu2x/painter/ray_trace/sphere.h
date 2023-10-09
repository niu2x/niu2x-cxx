#ifndef NIU2X_PAINTER_RAY_TRACE_SPHERE_H
#define NIU2X_PAINTER_RAY_TRACE_SPHERE_H

#include <niu2x/math.h>
#include <niu2x/painter/ray_trace/hittable.h>

namespace niu2x::painter::ray_trace {

using Vec3 = math::Vec3;
using Interval = math::Interval;
using Ray = math::Ray;

class Sphere : public Hittable {
public:
    Sphere(const Vec3& center, double radius, const SharedPtr<Material>& mat);
    Sphere(const Vec3& center, const Vec3& target_center, double radius,
        const SharedPtr<Material>& mat);

    virtual ~Sphere() = default;
    virtual Maybe<HitRecord> hit(
        const Ray& r, const Interval& ray_interval) const override;

    Vec3 center(double t) const { return center_ + center_vec_ * t; }

private:
    Vec3 center_;
    Vec3 center_vec_;
    bool movable_;

    double radius_;
    SharedPtr<Material> mat_;
};

} // namespace niu2x::painter::ray_trace

namespace niu2x::painter {
using RayTraceSphere = niu2x::painter::ray_trace::Sphere;
}

#endif