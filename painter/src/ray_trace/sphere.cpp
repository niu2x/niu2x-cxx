#include "sphere.h"
#include <niu2x/math.h>

namespace niu2x::painter::ray_trace {

Sphere::Sphere(
    const Vec3& center, double radius, const SharedPtr<Material>& mat)
: center_(center)
, radius_(radius)
, mat_(mat)
{
}

static HitRecord make_hit_record(const Ray& ray, double t, const Vec3& center,
    const SharedPtr<Material>& mat, double sign)
{
    HitRecord record;
    record.p = ray.at(t);
    record.t = t;
    record.material = mat;
    record.set_normal(ray.direction(), normalize(record.p - center) * sign);
    return record;
}

Maybe<HitRecord> Sphere::hit(const Ray& ray, const Interval& ray_interval) const
{
    auto oc = ray.origin() - center_;
    auto a = length2(ray.direction());
    auto half_b = dot(oc, ray.direction());
    auto c = length2(oc) - radius_ * radius_;
    auto discriminant = half_b * half_b - a * c;

    if (discriminant >= 0) {
        double sqrtd = sqrt(discriminant);
        double root = (-half_b - sqrtd) / a;
        if (ray_interval.surrounds(root)) {
            return make_hit_record(
                ray, root, center_, mat_, math::sign(radius_));
        } else {
            root = (-half_b + sqrtd) / a;
            if (ray_interval.surrounds(root)) {
                return make_hit_record(
                    ray, root, center_, mat_, math::sign(radius_));
            }
        }
    }
    return Maybe<HitRecord>();
}

} // namespace niu2x::painter::ray_trace