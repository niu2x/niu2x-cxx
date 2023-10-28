#ifndef NIU2X_PAINTER_RAY_TRACE_MATERIAL_H
#define NIU2X_PAINTER_RAY_TRACE_MATERIAL_H

#include <niu2x/type/color.h>
#include <niu2x/math.h>
#include <niu2x/unused.h>

namespace niu2x::painter::ray_trace {

using Vec3 = math::Vec3;
class HitRecord;

class Material {
public:
    virtual ~Material() = default;
    virtual bool scatter(const math::Ray& r_in, const HitRecord& rec,
        Vec3& attenuation, math::Ray& scattered) const = 0;

    virtual Vec3 emitted(double u, double v, const Vec3& p) const
    {
        unused(u);
        unused(v);
        unused(p);
        return Vec3(0, 0, 0);
    }
};

} // namespace niu2x::painter::ray_trace

namespace niu2x::painter {
using RayTraceMaterial = ray_trace::Material;
}

#endif