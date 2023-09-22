#ifndef NIU2X_IMAGE_H
#define NIU2X_IMAGE_H

#include <niu2x/type.h>

namespace niu2x {

class NXAPI Image : public Resource {
public:
    Image();
    virtual ~Image();
    virtual void store_to(WriteStream* dest) override;
    virtual void load_from(ReadStream* src) override;

private:
    IntSize size_;
    // int channel_;
    std::vector<Color> pixels_;
};

} // namespace niu2x

#endif
