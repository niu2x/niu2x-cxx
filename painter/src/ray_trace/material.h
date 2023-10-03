#ifndef NIU2X_PAINTER_RAY_TRACE_MATERIAL_H
#define NIU2X_PAINTER_RAY_TRACE_MATERIAL_H

#include <niu2x/type/color.h>
#include <niu2x/math/ray.h>

namespace niu2x::painter::ray_trace {

class Material {
public:
    virtual ~Material() = default;

    virtual bool scatter(const Ray& r_in, const HitRecord& rec,
        Color& attenuation, Ray& scattered) const = 0;
};

#endif