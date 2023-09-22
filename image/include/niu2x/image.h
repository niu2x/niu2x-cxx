#ifndef NIU2X_IMAGE_H
#define NIU2X_IMAGE_H

#include <niu2x/type.h>

namespace niu2x {

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

    void set_store_format(Format format) { store_format_ = format; }

private:
    IntSize size_;
    std::vector<Color> pixels_;
    Format store_format_;
};

} // namespace niu2x

#endif
