#include <niu2x/gfx/render_command.h>
#include <niu2x/gfx/draw.h>
#include <niu2x/gfx/gui.h>
#include <iostream>
#include <niu2x/gfx/resource_manager.h>
#include <niu2x/gfx/render_command_queue.h>

namespace niu2x::gfx {

RenderCommand::~RenderCommand() { }

} // namespace niu2x::gfx

namespace niu2x::gfx::render_command {

void Clear::run() { Draw::clear(); }

Clear::Clear() { }
Clear::~Clear() { }

void Triangles::run()
{
    vbo_->bind();
    if (veo_)
        veo_->bind();

    program_->bind();
    program_->set_uniforms(*uniforms_);

    for (Index i = 0; i < textures_.size(); i++) {
        if (textures_[i])
            textures_[i]->bind(i);
    }

    if (veo_) {
        Draw::draw_elements(0, veo_->size());
    } else {
        Draw::draw_arrays(0, vbo_->size());
    }
}

} // namespace niu2x::gfx::render_command