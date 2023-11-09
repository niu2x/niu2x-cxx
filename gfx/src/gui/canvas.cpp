#include <niu2x/gfx/gui/canvas.h>
#include <niu2x/gfx/render_command_queue.h>
#include <niu2x/gfx/render_command.h>
#include <niu2x/gfx/gfx_factory.h>
#include <niu2x/gfx/gui.h>
#include <niu2x/gfx/resource_manager.h>

namespace niu2x::gfx::gui {

Canvas::Canvas() { }

Canvas::~Canvas() { }

void Canvas::draw()
{
    auto rq = RenderCommandQueue::get();

    for (auto& c : commands_) {
        // std::visit(
        // [rq](auto& c) {
        // using T = decay<decltype(c)>;
        // if constexpr (is_same<T, ImageCommand>) {

        // UniformPacket uniforms;

        // rc::Triangles::InitParam init { arg.vbo.get(),
        //                                 arg.veo.get(),
        //                                 RenderProgramID::COLOR,
        //                                 move(uniforms) };
        // auto render_cmd = rcf->create_triangles(move(init));
        c.draw.set_uniforms(&c.uniforms);
        rq->enqueue(&c.draw);
        // }
        // },
        // c);
    }
}

void Canvas::clear() { commands_.clear(); }

void Canvas::add_image(ImageSheet::Frame* frame, const Rect& r)
{
    commands_.emplace_back(r, frame);
}

Canvas::ImageCommand::ImageCommand(const Rect& r, ImageSheet::Frame* f)
: rect(r)
, frame(f)
{
    static_assert(is_movable<ImageCommand>);

    vbo = GFX_Factory::get()->create_vertex_buffer();
    veo = GFX_Factory::get()->create_index_buffer();

    vbo->resize(16);
    veo->resize(9 * 2 * 3);

    Vertex vertexs[16];
    uint16_t indexes[9 * 2 * 3];

    auto region = frame->region();

    int elem_index = 0;

    float x_offset[] = {
        0,
        region.size.width / 3.0f,
        rect.size.width - region.size.width / 3.0f,
        rect.size.width,
    };

    float y_offset[] = {
        0,
        region.size.height / 3.0f,
        rect.size.height - region.size.height / 3.0f,
        rect.size.height,
    };

    auto tex_size = frame->texture()->size();

    for (int x = 0; x < 4; x++) {
        for (int y = 0; y < 4; y++) {
            int index = y * 4 + x;
            vertexs[index].r = 1;
            vertexs[index].g = 1;
            vertexs[index].b = 1;
            vertexs[index].a = 1;
            vertexs[index].u = region.origin.x + region.size.width * x / 3.0f;
            vertexs[index].u /= tex_size.width;
            vertexs[index].v = region.origin.y + region.size.height * y / 3.0f;
            vertexs[index].v /= tex_size.height;

            vertexs[index].z = 0.0;
            vertexs[index].x = rect.origin.x + x_offset[x];
            vertexs[index].y = -rect.origin.y - y_offset[y];

            if (x < 3 && y < 3) {
                indexes[elem_index++] = index;
                indexes[elem_index++] = 4 + index;
                indexes[elem_index++] = 5 + index;

                indexes[elem_index++] = index;
                indexes[elem_index++] = 5 + index;
                indexes[elem_index++] = 1 + index;
            }
        }
    }

    vbo->set_vertexs(0, 16, vertexs);
    veo->set(0, 54, indexes);

    using Uniform = RenderProgram::Uniform;
    uniforms[Uniform::MODEL] = unit_mat4;
    uniforms[Uniform::VIEW] = gui::ui_view_mat4;
    uniforms[Uniform::PROJECTION] = gui::ui_projection_mat4;
    uniforms[Uniform::TEX_0] = 0;
    uniforms[Uniform::MASK_COLOR] = Color { 1, 1, 1, 0.3 };

    draw.set_vbo(vbo.get());
    draw.set_veo(veo.get());
    auto res_mgr = ResourceManager::get();
    auto prog = res_mgr->get_render_program(RenderProgramID::TEXTURE_COLOR);
    draw.set_program(prog);
    draw.set_uniforms(&uniforms);
    draw.set_texture(0, f->texture());
}

} // namespace niu2x::gfx::gui