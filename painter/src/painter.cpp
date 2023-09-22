#include <niu2x/painter.h>
#include "learning_0_1.h"

namespace niu2x::painter {

Painter::~Painter() { }

UniquePtr<Painter> Painter::create(PainterType type)
{
    switch (type) {
        case PainterType::LEARNING_0_1: {
            return make_unique<painter::Learning_0_1>();
        }
    }
    return nullptr;
}

} // namespace niu2x::painter
