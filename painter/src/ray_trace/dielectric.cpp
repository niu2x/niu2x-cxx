#include <niu2x/type.h>
#include <niu2x/painter/ray_trace/dielectric.h>
#include <niu2x/math/utils.h>
#include "math.h"

namespace niu2x::painter::ray_trace {

static double reflectance(double cosine, double ref_idx)
{
    // Use Schlick's approximation for reflectance.
    auto r0 = (1 - ref_idx) / (1 + ref_idx);
    r0 = r0 * r0;
    return r0 + (1 - r0) * pow((1 - cosine), 5);
}

bool Dielectric::scatter(const Ray& r_in, const HitRecord& rec,
    Vec3& attenuation, Ray& scattered) const
{
    Vec3 unit_direction = normalize(r_in.direction());
    double refraction_ratio = rec.front_face ? (1.0 / ir_) : ir_;

    attenuation = Vec3(1.0, 1.0, 1.0);

    double cos_theta = fabs(dot(unit_direction, rec.normal));
    double sin_theta = sqrt(1.0 - cos_theta * cos_theta);

    bool connot_refract = refraction_ratio * sin_theta > 1.0;
    bool random_reflect
        = reflectance(cos_theta, refraction_ratio) > math::random<double>();

    if (connot_refract || random_reflect) {
        Vec3 reflected = reflect(unit_direction, rec.normal);
        scattered = Ray(rec.p, normalize(reflected), r_in.time());
        return true;
    } else {
        Vec3 refracted = refract(unit_direction, rec.normal, refraction_ratio);
        scattered = Ray(rec.p, normalize(refracted), r_in.time());
        return true;
    }
}

} // namespace niu2x::painter::ray_trace