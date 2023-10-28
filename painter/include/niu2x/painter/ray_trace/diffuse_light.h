#ifndef NIU2X_PAINTER_RAY_TRACE_DIFFUSE_LIGHT_H
#define NIU2X_PAINTER_RAY_TRACE_DIFFUSE_LIGHT_H

#include <niu2x/type/color.h>
#include <niu2x/math.h>
#include <niu2x/painter/ray_trace/material.h>
#include <niu2x/painter/ray_trace/texture.h>

namespace niu2x::painter::ray_trace {

using Ray = math::Ray;
using Vec3 = math::Vec3;
class HitRecord;

class DiffuseLight : public Material {
public:
    DiffuseLight(SPtr<Texture> a)
    : emit_(a)
    {
    }
    DiffuseLight(const Vec3& c)
    : emit_(make_shared<SolidColor>(math::to_color(c)))
    {
    }

    bool scatter(const Ray& r_in, const HitRecord& rec, Vec3& attenuation,
        Ray& scattered) const override
    {
        unused(r_in);
        unused(rec);
        unused(attenuation);
        unused(scattered);
        return false;
    }

    Vec3 emitted(double u, double v, const Vec3& p) const override
    {
        static double scale = 1 / 255.0;
        auto color = emit_->value(u, v, p);
        return Vec3(color.r * scale, color.g * scale, color.b * scale);
    }

private:
    SPtr<Texture> emit_;
};

} // namespace niu2x::painter::ray_trace

#endif