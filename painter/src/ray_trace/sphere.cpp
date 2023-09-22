#include "sphere.h"
#include <niu2x/math.h>

namespace niu2x::painter::ray_trace {

Sphere::Sphere(const Vec3& center, double radius)
: center_(center)
, radius_(radius)
{
}

Optional<HitRecord> Sphere::hit(const Ray& ray, double min, double max) const
{
    double t = math::hit_sphere(center_, radius_, ray);
    if (t >= 0) {
        if (t >= min && t <= max) {
            HitRecord record;
            record.p = ray.at(t);
            record.t = t;
            record.normal = normalize(record.p - center_);
            return record;
        }
    }
    return Optional<HitRecord>();
}

} // namespace niu2x::painter::ray_trace