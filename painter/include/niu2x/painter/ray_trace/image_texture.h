#ifndef NIU2X_PAINTER_RAY_TRACE_IMAGE_TEXTURE_H
#define NIU2X_PAINTER_RAY_TRACE_IMAGE_TEXTURE_H

#include <niu2x/painter/ray_trace/texture.h>
#include <niu2x/image.h>
#include <niu2x/fs.h>
#include <niu2x/math/size.h>

namespace niu2x::painter::ray_trace {

class ImageTexture : public Texture {
public:
    ImageTexture(const fs::Path& path);
    Vec3 value(double u, double v, const Vec3& p) const override;

private:
    image::Image image_;
    math::IntSize size_;
};

} // namespace niu2x::painter::ray_trace

#endif