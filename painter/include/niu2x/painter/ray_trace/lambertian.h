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
    : albedo_(a)
    {
    }

    Lambertian(SPtr<Texture> tex)
    : texture_(tex)
    {
    }

    bool scatter(const Ray& r_in, const HitRecord& rec, math::Vec3& attenuation,
        Ray& scattered) const override;

private:
    math::Vec3 albedo_;
    SPtr<Texture> texture_;
};

} // namespace niu2x::painter::ray_trace

namespace niu2x::painter {
using RayTraceLambertian = ray_trace::Lambertian;
}

#endif