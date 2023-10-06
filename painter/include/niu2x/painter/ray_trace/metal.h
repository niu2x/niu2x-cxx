#ifndef NIU2X_PAINTER_RAY_TRACE_METAL_H
#define NIU2X_PAINTER_RAY_TRACE_METAL_H

#include <niu2x/type/color.h>
#include <niu2x/math.h>
#include <niu2x/painter/ray_trace/material.h>

namespace niu2x::painter::ray_trace {

using Ray = math::Ray;
using Vec3 = math::Vec3;
class HitRecord;

class Metal : public Material {
public:
    Metal(const Vec3& a, double f)
    : albedo_(a)
    , fuzz_(math::clamp(f, 0.0, 1.0))
    {
    }
    bool scatter(const Ray& r_in, const HitRecord& rec, Vec3& attenuation,
        Ray& scattered) const override;

private:
    Vec3 albedo_;
    double fuzz_;
};

} // namespace niu2x::painter::ray_trace

namespace niu2x::painter {
using RayTraceMetal = ray_trace::Metal;
}
#endif