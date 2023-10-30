#ifndef NIU2X_IMAGE_H
#define NIU2X_IMAGE_H

#include <niu2x/type.h>
#include <niu2x/math/geometry.h>

namespace niu2x::image {

using math::IntSize;

class NXAPI Image : public Resource {
public:
    enum class Format {
        PNG,
        JPG,
    };

    Image();
    virtual ~Image();

    virtual void store_to(WriteStream* dest) override;
    virtual void load_from(ReadStream* src) override;

    void reset(int w, int h, const Color& color);

    void set_store_format(Format format) { store_format_ = format; }

    const IntSize& size() const { return size_; }

    void set_pixel(int row, int col, const Color& c)
    {
        pixels_[row * size_.width + col] = c;
    }

    Color& pixel(int row, int col) { return pixels_[row * size_.width + col]; }

    const Color& pixel(int row, int col) const
    {
        return pixels_[row * size_.width + col];
    }

private:
    IntSize size_;
    std::vector<Color> pixels_;
    Format store_format_;
};

} // namespace niu2x::image

#endif
