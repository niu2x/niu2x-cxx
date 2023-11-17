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
        c.draw.set_uniforms(&c.uniforms);
        rq->enqueue(&c.draw);
    }
}

void Canvas::clear() { commands_.clear(); }

void Canvas::add_image(const ImageSheet::Frame& frame, const Rect& r)
{
    ImageCommand cmd { r, frame, false };
    commands_.emplace_back(move(cmd));
}

void Canvas::add_image(
    const ImageSheet::Frame& frame,
    const Rect& r,
    RenderProgram* prog)
{
    ImageCommand cmd { r, frame, false, prog };
    commands_.emplace_back(move(cmd));
}

void Canvas::add_image(
    const ImageSheet::Frame& frame,
    const Rect& r,
    bool scale9)
{
    commands_.emplace_back(r, frame, scale9);
}

Canvas::ImageCommand::ImageCommand(
    const Rect& r,
    const ImageSheet::Frame& f,
    bool scale9,
    RenderProgram* prog)
: rect(r)
, frame(f)
, scale9(scale9)
, program(prog)
{
    static_assert(type_pred::is_movable<ImageCommand>);

    vbo = GFX_Factory::get()->create_vertex_buffer();
    veo = GFX_Factory::get()->create_index_buffer();

    if (scale9) {

        vbo->resize(16);
        veo->resize(9 * 2 * 3);

        Vertex vertexs[16];
        uint16_t indexes[9 * 2 * 3];

        auto region = frame.region();

        int elem_index = 0;

        auto tmp_w = min<float>(rect.size.width, region.size.width);
        float x_offset[] = {
            0,
            tmp_w / 3.0f,
            rect.size.width - tmp_w / 3.0f,
            rect.size.width,
        };

        auto tmp_h = min<float>(rect.size.height, region.size.height);
        float y_offset[] = {
            0,
            tmp_h / 3.0f,
            rect.size.height - tmp_h / 3.0f,
            rect.size.height,
        };

        auto tex_size = frame.texture()->size();

        for (int x = 0; x < 4; x++) {
            for (int y = 0; y < 4; y++) {
                int index = y * 4 + x;
                vertexs[index].r = 1;
                vertexs[index].g = 1;
                vertexs[index].b = 1;
                vertexs[index].a = 1;

                vertexs[index].u
                    = region.origin.x + region.size.width * x / 3.0f;
                vertexs[index].u /= tex_size.width;
                vertexs[index].v
                    = region.origin.y + region.size.height * y / 3.0f;
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

    } else {

        vbo->resize(4);
        veo->resize(6);

        Vertex vertexs[4];
        uint16_t indexes[6];

        auto region = frame.region();

        int elem_index = 0;

        float x_offset[] = {
            0,
            rect.size.width,
        };

        float y_offset[] = {
            0,
            rect.size.height,
        };

        auto tex_size = frame.texture()->size();

        for (int x = 0; x < 2; x++) {
            for (int y = 0; y < 2; y++) {
                int index = y * 2 + x;
                vertexs[index].r = 1;
                vertexs[index].g = 1;
                vertexs[index].b = 1;
                vertexs[index].a = 1;

                vertexs[index].u = region.origin.x + region.size.width * x;
                vertexs[index].u /= tex_size.width;
                vertexs[index].v = region.origin.y + region.size.height * y;
                vertexs[index].v /= tex_size.height;

                vertexs[index].z = 0.0;
                vertexs[index].x = rect.origin.x + x_offset[x];
                vertexs[index].y = -rect.origin.y - y_offset[y];

                if (x < 1 && y < 1) {
                    indexes[elem_index++] = index;
                    indexes[elem_index++] = 2 + index;
                    indexes[elem_index++] = 3 + index;

                    indexes[elem_index++] = index;
                    indexes[elem_index++] = 3 + index;
                    indexes[elem_index++] = 1 + index;
                }
            }
        }

        vbo->set_vertexs(0, 4, vertexs);
        veo->set(0, 6, indexes);
    }
    using Uniform = RenderProgram::Uniform;
    uniforms[Uniform::MODEL] = unit_mat4;
    uniforms[Uniform::VIEW] = gui::ui_view_mat4;
    uniforms[Uniform::PROJECTION] = gui::ui_projection_mat4;
    uniforms[Uniform::TEX_0] = 0;
    uniforms[Uniform::MASK_COLOR] = Color { 1, 1, 1, 1 };

    draw.set_vbo(vbo.get());
    draw.set_veo(veo.get());
    auto res_mgr = ResourceManager::get();
    program = program
        ?: res_mgr->get_render_program(RenderProgramID::TEXTURE_COLOR);
    draw.set_program(program);
    draw.set_uniforms(&uniforms);
    draw.set_texture(0, f.texture());
}

} // namespace niu2x::gfx::gui