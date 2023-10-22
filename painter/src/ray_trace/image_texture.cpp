#include <niu2x/painter/ray_trace/image_texture.h>
#include <niu2x/stream.h>

namespace niu2x::painter::ray_trace {

ImageTexture::ImageTexture(const fs::Path& path)
{
    fs::File file(path);
    stream::FileReadStream fin(file);
    image_.load_from(&fin);
    size_ = image_.size();
}

Color ImageTexture::value(double u, double v, const Vec3& p) const
{
    unused(p);
    int row = (1 - v) * size_.height;
    int col = u * size_.width;
    return image_.pixel(row, col);
}

} // namespace niu2x::painter::ray_trace