#include <niu2x/gfx/render_command.h>
#include <niu2x/gfx/draw.h>

namespace niu2x::gfx {

RenderCommand::~RenderCommand() { }

} // namespace niu2x::gfx

namespace niu2x::gfx::render_command {

void Clear::run() { Draw::clear(); }

Clear::Clear() { }
Clear::~Clear() { }

} // namespace niu2x::gfx::render_command