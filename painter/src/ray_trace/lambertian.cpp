#include <niu2x/painter/ray_trace/lambertian.h>
#include <niu2x/type.h>
#include <niu2x/math/utils.h>
#include "math.h"

namespace niu2x::painter::ray_trace {

bool Lambertian::scatter(const Ray& r_in, const HitRecord& rec,
    math::Vec3& attenuation, Ray& scattered) const
{
    unused(r_in);
    auto scatter_direction = rec.normal + random_unit_vec3();
    scattered = Ray(rec.p, scatter_direction, r_in.time());
    attenuation = albedo_->value(rec.u, rec.v, rec.p);
    return true;
}

} // namespace niu2x::painter::ray_trace