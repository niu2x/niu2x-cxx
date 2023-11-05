#include <niu2x/gfx/render_command.h>
#include <niu2x/gfx/draw.h>
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
    vb_->bind();
    auto* program = ResourceManager::get()->get_render_program(program_id_);
    program->bind();
    program->set_uniforms(uniforms_);
    Draw::draw_triangles(0, vb_->size());
}

DrawRect::DrawRect(const Rect& rect, const Color& color)
: rect_(rect)
, color_(color)
{
}

DrawRect::~DrawRect() { }

void DrawRect::run()
{
    using Uniform = RenderProgram::Uniform;

    auto res_mgr = ResourceManager::get();
    auto rf = RenderCommandFactory::get();
    UniformPacket uniforms;

    uniforms[Uniform::MODEL] = mul(math::translation_matrix(Vec3(rect_.origin.x,
                                       -rect_.origin.y - rect_.size.height, 0)),
        math::scaling_matrix(Vec3(rect_.size.width, rect_.size.height, 1)));

    // uniforms[Uniform::MODEL] = unit_mat4;
    uniforms[Uniform::VIEW] = math::lookat_matrix(
        Vec3(640 / 2, -480 / 2, 10), Vec3(640 / 2, -480 / 2, 0), Vec3(0, 1, 0));

    uniforms[Uniform::PROJECTION] = math::frustum_matrix<float>(
        -640 / 2, 640 / 2, -480 / 2, 480 / 2, -100, 100);

    auto square_vb = res_mgr->get_vertex_buffer("common/vb/square");
    auto program_id = RenderProgramID::COLOR;
    auto cmd = rf->create_triangles(square_vb, program_id, move(uniforms));
    cmd->run();
    rf->destroy(cmd);
}

} // namespace niu2x::gfx::render_command