#ifndef NIU2X_PAINTER_RAY_TRACE_NOISE_TEXTURE_H
#define NIU2X_PAINTER_RAY_TRACE_NOISE_TEXTURE_H

#include <niu2x/painter/ray_trace/texture.h>
#include <niu2x/math/perlin.h>

namespace niu2x::painter::ray_trace {

class NoiseTexture : public Texture {
public:
    NoiseTexture() { }
    NoiseTexture(double sc)
    : scale_(sc)
    {
    }
    Vec3 value(double u, double v, const Vec3& p) const override
    {
        unused(u);
        unused(v);
        // return math::to_color(Vec3(1, 1, 1) * noise_.turb(p * scale_));

        auto s = scale_ * p;
        return Vec3(1, 1, 1) * 0.5 * (1 + sin(s.z + 10 * noise_.turb(s)));
    }

private:
    math::Perlin noise_;
    double scale_ = 1;
};

} // namespace niu2x::painter::ray_trace

#endif