#include <niu2x/gfx/window_factory.h>
#include "glfw_window.h"

namespace niu2x::gfx {

UniquePtr<Window> WindowFactory::create_window()
{
    return make_unique<GLFW_WindowWithRenderContext>();
}

} // namespace niu2x::gfx