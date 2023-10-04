#include "metal.h"
#include <niu2x/type.h>
#include <niu2x/math/utils.h>
#include "math.h"

namespace niu2x::painter::ray_trace {

bool Metal::scatter(const Ray& r_in, const HitRecord& rec, Vec3& attenuation,
    Ray& scattered) const
{
    Vec3 reflected = reflect(normalize(r_in.direction()), rec.normal);
    scattered = Ray(rec.p, reflected + fuzz_ * math::random<Vec3>());
    attenuation = albedo_;
    return dot(scattered.direction(), rec.normal) > 0;
}

} // namespace niu2x::painter::ray_trace