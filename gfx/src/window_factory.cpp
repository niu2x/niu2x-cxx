#include <niu2x/gfx/window_factory.h>
#include "glfw_window.h"
#include "global_vars.h"

namespace niu2x::gfx {

UniquePtr<Window> WindowFactory::create_window()
{
    auto win = make_unique<GLFW_WindowWithRenderContext>();
    if (!__main_window)
        __main_window = win.get();
    return win;
}

} // namespace niu2x::gfx