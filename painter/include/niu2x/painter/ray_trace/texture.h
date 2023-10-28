#ifndef NIU2X_PAINTER_RAY_TRACE_TEXTURE_H
#define NIU2X_PAINTER_RAY_TRACE_TEXTURE_H

#include <niu2x/type/color.h>
#include <niu2x/unused.h>
#include <niu2x/math.h>

namespace niu2x::painter::ray_trace {

using Vec3 = math::Vec3;

class Texture {
public:
    virtual ~Texture() = default;

    virtual Vec3 value(double u, double v, const Vec3& p) const = 0;
};

class SolidColor : public Texture {
public:
    SolidColor(const Vec3& c)
    : color_value_(c)
    {
    }

    Vec3 value(double u, double v, const Vec3& p) const override
    {
        unused(u);
        unused(v);
        unused(p);
        return color_value_;
    }

private:
    Vec3 color_value_;
};

class CheckerTexture : public Texture {
public:
    CheckerTexture(double _scale, SPtr<Texture> _even, SPtr<Texture> _odd)
    : inv_scale_(1.0 / _scale)
    , even_(_even)
    , odd_(_odd)
    {
    }

    CheckerTexture(double _scale, const Vec3& c1, const Vec3& c2)
    : inv_scale_(1.0 / _scale)
    , even_(make_shared<SolidColor>(c1))
    , odd_(make_shared<SolidColor>(c2))
    {
    }

    Vec3 value(double u, double v, const Vec3& p) const override
    {
        auto xInteger = static_cast<int>(floor(inv_scale_ * p.x));
        auto yInteger = static_cast<int>(floor(inv_scale_ * p.y));
        auto zInteger = static_cast<int>(floor(inv_scale_ * p.z));
        bool isEven = (xInteger + yInteger + zInteger) % 2 == 0;
        return isEven ? even_->value(u, v, p) : odd_->value(u, v, p);
    }

private:
    double inv_scale_;
    SPtr<Texture> even_;
    SPtr<Texture> odd_;
};

} // namespace niu2x::painter::ray_trace

#endif