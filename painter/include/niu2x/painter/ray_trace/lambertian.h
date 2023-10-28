#ifndef NIU2X_PAINTER_RAY_TRACE_LAMBERTIAN_H
#define NIU2X_PAINTER_RAY_TRACE_LAMBERTIAN_H

#include <niu2x/type/color.h>
#include <niu2x/math.h>
#include <niu2x/painter/ray_trace/material.h>
#include <niu2x/painter/ray_trace/texture.h>

namespace niu2x::painter::ray_trace {

using Ray = math::Ray;
class HitRecord;

class Lambertian : public Material {
public:
    Lambertian(const math::Vec3& a)
    : albedo_(make_shared<SolidColor>(Vec3((a.x), (a.y), (a.z))))
    {
    }

    Lambertian(SPtr<Texture> tex)
    : albedo_(tex)
    {
    }

    bool scatter(const Ray& r_in, const HitRecord& rec, math::Vec3& attenuation,
        Ray& scattered) const override;

private:
    SPtr<Texture> albedo_;
};

} // namespace niu2x::painter::ray_trace

namespace niu2x::painter {
using RayTraceLambertian = ray_trace::Lambertian;
}

#endif