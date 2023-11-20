#include <atomic>
#include <niu2x/gfx/gui/text.h>
#include <niu2x/gfx/resource_manager.h>
#include <niu2x/string_utils.h>

namespace niu2x::gfx::gui {

Text::Text() { }

Text::~Text() { }

void Text::update_canvas()
{
    auto c = canvas();
    c->clear();
    auto r = compute_self_rect();
    if (r.size.area() <= 0)
        return;

    auto res_mgr = ResourceManager::get();
    auto program = res_mgr->get_render_program(RenderProgramID::TEXT);
    auto maybe = string_utils::utf8_to_utf32(text_);
    if (maybe) {
        font_->prepare(*maybe);

        math::Pos2D<float> pen = r.origin;
        pen.y += font_->line_height();

        for (auto ch : *maybe) {
            auto& ch_info = font_->get_char_info(ch);
            auto tex = font_->get_texture(ch_info.tex);
            c->add_image(
                ImageSheet::Frame(tex, ch_info.region),
                { pen.x + ch_info.x_offset,
                  pen.y + ch_info.y_offset,
                  (float)ch_info.region.size.width,
                  (float)ch_info.region.size.height },
                program);
            pen.x += ch_info.x_advance;
        }
    }
}

} // namespace niu2x::gfx::gui