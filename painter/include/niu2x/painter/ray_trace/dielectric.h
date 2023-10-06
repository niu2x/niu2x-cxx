#ifndef NIU2X_PAINTER_RAY_TRACE_DIELECTRIC_H
#define NIU2X_PAINTER_RAY_TRACE_DIELECTRIC_H

#include <niu2x/type/color.h>
#include <niu2x/math.h>
#include <niu2x/painter/ray_trace/material.h>

namespace niu2x::painter::ray_trace {

using Ray = math::Ray;
using Vec3 = math::Vec3;
class HitRecord;

class Dielectric : public Material {
public:
    Dielectric(double index_of_refraction)
    : ir_(index_of_refraction)
    {
    }

    bool scatter(const Ray& r_in, const HitRecord& rec, Vec3& attenuation,
        Ray& scattered) const override;

private:
    double ir_;
};

} // namespace niu2x::painter::ray_trace

namespace niu2x::painter {
using RayTraceDielectric = ray_trace::Dielectric;
}

#endif