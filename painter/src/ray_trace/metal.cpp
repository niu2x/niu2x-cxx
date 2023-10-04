#include "metal.h"
#include <niu2x/type.h>
#include <niu2x/math/utils.h>
#include "math.h"

namespace niu2x::painter::ray_trace {

bool Metal::scatter(const Ray& r_in, const HitRecord& rec, Vec3& attenuation,
    Ray& scattered) const
{
    Vec3 reflected = reflect(normalize(r_in.direction()), rec.normal);
    scattered = Ray(rec.p, reflected);
    attenuation = albedo_;
    return true;
}

} // namespace niu2x::painter::ray_trace