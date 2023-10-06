#include <niu2x/painter.h>
#include "ray_trace.h"

namespace niu2x::painter {

Painter::~Painter() { }

UniquePtr<Painter> Painter::create(PainterType type)
{
    switch (type) {
        case PainterType::RAY_TRACE: {
            return make_unique<painter::RayTracePainter>();
        }
    }
    return nullptr;
}

} // namespace niu2x::painter
