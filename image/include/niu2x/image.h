#ifndef NIU2X_IMAGE_H
#define NIU2X_IMAGE_H

#include <niu2x/type.h>

namespace niu2x {

class NXAPI Image : public Resource {
public:
    Image();
    virtual ~Image();
    virtual void store_to(WriteStream* src) override;
    virtual void load_from(ReadStream* src) override;

private:
    uint16_t width_;
    uint16_t height_;
    std::vector<Color> pixels_;
};

} // namespace niu2x

#endif
