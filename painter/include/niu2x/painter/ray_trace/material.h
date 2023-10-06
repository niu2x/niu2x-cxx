#ifndef NIU2X_PAINTER_RAY_TRACE_MATERIAL_H
#define NIU2X_PAINTER_RAY_TRACE_MATERIAL_H

#include <niu2x/type/color.h>
#include <niu2x/math.h>

namespace niu2x::painter::ray_trace {

class HitRecord;

class Material {
public:
    virtual ~Material() = default;
    virtual bool scatter(const math::Ray& r_in, const HitRecord& rec,
        math::Vec3& attenuation, math::Ray& scattered) const = 0;
};

} // namespace niu2x::painter::ray_trace

namespace niu2x::painter {
using RayTraceMaterial = ray_trace::Material;
}

#endif