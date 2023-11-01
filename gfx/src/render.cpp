#include <niu2x/gfx/simple_function.h>
#include <niu2x/gfx/render_command_queue.h>

namespace niu2x::gfx {

void render() { RenderCommandQueue::get()->render(); }

} // namespace niu2x::gfx
