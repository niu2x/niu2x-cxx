#ifndef NIU2X_IMAGE_IMAGE_DATA_H
#define NIU2X_IMAGE_IMAGE_DATA_H

#include <niu2x/type.h>
#include <niu2x/math/geometry.h>

namespace niu2x::image {

using math::IntSize;

class NXAPI ImageData : public Resource {
public:
    enum class Format {
        PNG,
        JPG,
    };

    NIU2X_CLASS_DEFAULT_MOVABLE(ImageData);
    NIU2X_CLASS_DEFAULT_COPYABLE(ImageData);

    ImageData();
    virtual ~ImageData();

    virtual void store_to(WriteStream* dest) override;
    virtual void load_from(ReadStream* src) override;

    void reset(int w, int h, int channels);

    void set_store_format(Format format) { store_format_ = format; }

    const IntSize& size() const { return size_; }
    int channels() const { return channels_; }

    const uint8_t* data() const { return pixels_.data(); }

private:
    IntSize size_;
    std::vector<uint8_t> pixels_;
    Format store_format_;
    int channels_;
};
static_assert(is_movable<ImageData>);

} // namespace niu2x::image

#endif
