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

    auto* program = ResourceManager::get()->get_render_program(program_id_);
    program->bind();
    program->set_uniforms(uniforms_);

    if (veo_) {
        Draw::draw_elements(0, veo_->size());
    } else {
        Draw::draw_arrays(0, vbo_->size());
    }
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

    auto translate = math::translation_matrix(
        Vec3(rect_.origin.x, -rect_.origin.y - rect_.size.height, 0));

    auto scaling
        = math::scaling_matrix(Vec3(rect_.size.width, rect_.size.height, 1));

    uniforms[Uniform::MODEL] = mul(translate, scaling);
    uniforms[Uniform::MASK_COLOR] = color_;
    uniforms[Uniform::VIEW] = gui::ui_view_mat4;
    uniforms[Uniform::PROJECTION] = gui::ui_projection_mat4;

    auto square_vb = res_mgr->get_vertex_buffer("common/vb/square");
    auto program_id = RenderProgramID::COLOR;
    auto cmd = rf->create_triangles(square_vb, program_id, move(uniforms));
    cmd->run();
    rf->destroy(cmd);
}

DrawUI::~DrawUI() { }

DrawUI::DrawUI(VertexBuffer* vbo, ImageSheet::Frame* frame, bool scale9)
: vbo_(vbo)
, frame_(frame)
,scale9_(scale9)
{
}

DrawUI::DrawUI(
    VertexBuffer* vbo, IndexBuffer* veo, ImageSheet::Frame* frame, bool scale9)
: vbo_(vbo)
, veo_(veo)
, frame_(frame)
, scale9_(scale9)
{
}

DrawUI::DrawUI(const Rect& rect, ImageSheet::Frame* frame)
: rect_(rect)
, frame_(frame)
{
}

void DrawUI::run()
{
    using Uniform = RenderProgram::Uniform;
    auto res_mgr = ResourceManager::get();
    UniformPacket uniforms;

    if (!vbo_) {

        auto translate = math::translation_matrix(
            Vec3(rect_.origin.x, -rect_.origin.y - rect_.size.height, 0));

        auto scaling = math::scaling_matrix(
            Vec3(rect_.size.width, rect_.size.height, 1));

        uniforms[Uniform::MODEL] = mul(translate, scaling);

        uniforms[Uniform::VIEW] = gui::ui_view_mat4;
        uniforms[Uniform::PROJECTION] = gui::ui_projection_mat4;
        uniforms[Uniform::TEX_0] = 0;

        frame_->texture()->bind(0);

        auto square_vb = res_mgr->get_vertex_buffer("common/vb/square");
        auto program_id = RenderProgramID::TEXTURE_COLOR;

        Triangles triangles({ square_vb, nullptr, program_id, move(uniforms) });
        triangles.run();

    } else {

        uniforms[Uniform::MODEL] = unit_mat4;
        uniforms[Uniform::VIEW] = gui::ui_view_mat4;
        uniforms[Uniform::PROJECTION] = gui::ui_projection_mat4;
        uniforms[Uniform::TEX_0] = 0;
        frame_->texture()->bind(0);
        auto program_id = RenderProgramID::TEXTURE_COLOR;
        Triangles triangles({ vbo_, veo_, program_id, move(uniforms) });
        triangles.run();
    }
}

} // namespace niu2x::gfx::render_command