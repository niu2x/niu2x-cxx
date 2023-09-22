#include <niu2x/painter.h>
#include "learning_0_1.h"
#include "ray_trace.h"

namespace niu2x::painter {

Painter::~Painter() { }

UniquePtr<Painter> Painter::create(PainterType type)
{
    switch (type) {
        case PainterType::LEARNING_0_1: {
            return make_unique<painter::Learning_0_1>();
        }
        case PainterType::RAY_TRACE: {
            return make_unique<painter::RayTracePainter>();
        }
    }
    return nullptr;
}

} // namespace niu2x::painter
