#ifndef NIU2X_IMAGE_IMAGE_H
#define NIU2X_IMAGE_IMAGE_H

#include <niu2x/std_alias.h>
#include <niu2x/preprocess.h>
#include <niu2x/resource.h>
#include <niu2x/math/geometry.h>

namespace niu2x::image {
enum class FileFormat {
    PNG,
    JPG,
};

using math::IntSize;
class Image : public Resource {
public:
    Image();
    virtual ~Image();

    NIU2X_PP_MOVABLE(Image);
    NIU2X_PP_COPYABLE(Image);

    virtual void store_to(ByteWriteStream* dst) const override;
    virtual void load_from(ByteReadStream* src) override;

    // void reset(int w, int h, const Color& color);
    void set_store_format(FileFormat format) { store_format_ = format; }

    const IntSize& size() const { return size_; }

    // void set_pixel(int row, int col, const Color& c)
    // {
    //     pixels_[row * size_.width + col] = c;
    // }

    // Color& pixel(int row, int col) { return pixels_[row * size_.width + col];
    // }

    // const Color& pixel(int row, int col) const
    // {
    //     return pixels_[row * size_.width + col];
    // }

private:
    IntSize size_;
    std::vector<uint8_t> pixels_;

    // bytes per pixel
    int bytes_per_channel = 1;
    int channels_ = 1;

    mutable FileFormat store_format_ = FileFormat::PNG;
};

static_assert(type_pred::is_movable<Image>);

} // namespace niu2x::image

#endif
