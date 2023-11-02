#include <niu2x/gfx/render_command.h>
#include <niu2x/gfx/draw.h>
#include <niu2x/gfx/resource_manager.h>

namespace niu2x::gfx {

RenderCommand::~RenderCommand() { }

} // namespace niu2x::gfx

namespace niu2x::gfx::render_command {

void Clear::run() { Draw::clear(); }

Clear::Clear() { }
Clear::~Clear() { }

void Triangles::run()
{
    vb_->bind();
    auto* program = ResourceManager::get()->get_render_program(program_id_);
    program->bind();
    program->set_uniforms(uniforms_);
    Draw::draw_triangles(0, vb_->size());
}

} // namespace niu2x::gfx::render_command