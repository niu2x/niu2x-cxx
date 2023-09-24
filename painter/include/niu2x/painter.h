#ifndef NIU2X_PAINTER_H
#define NIU2X_PAINTER_H

#include <niu2x/type.h>
#include <niu2x/image.h>
#include <niu2x/painter/painter_type.h>

namespace niu2x::painter {

using image::Image;

class NXAPI Painter {
public:
    static UniquePtr<Painter> create(PainterType);

    virtual ~Painter() = 0;

    virtual void paint(Image* image) = 0;
};

} // namespace niu2x::painter

#endif
