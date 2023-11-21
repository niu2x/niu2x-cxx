#include <atomic>
#include <niu2x/gfx/gui/text.h>
#include <niu2x/gfx/resource_manager.h>
#include <niu2x/string_utils.h>

namespace niu2x::gfx::gui {

Text::Text() { set_measure(); }

Text::~Text() { }

math::Size<float> Text::measure(const SizeRange& size_range)
{

    math::Size<float> size;
    int line_count = 1;
    auto maybe = string_utils::utf8_to_utf32(text_);
    if (maybe) {
        font_->prepare(*maybe);

        math::Pos2D<float> pen;

        for (auto ch : *maybe) {
            auto& ch_info = font_->get_char_info(ch);
            // if(pen.x + )
            auto new_width = pen.x + (float)ch_info.region.size.width;
            if (new_width > size_range.max.width) {
                line_count++;
                pen.x = 0;
                new_width = pen.x + (float)ch_info.region.size.width;
            }
            size.width = max(new_width, size.width);
            pen.x += ch_info.x_advance;
        }
    }
    size.height = font_->line_height() * line_count;
    return size;
}

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
        pen.y += font_->line_height() + font_->baseline();

        for (auto ch : *maybe) {
            auto& ch_info = font_->get_char_info(ch);
            auto tex = font_->get_texture(ch_info.tex);

            if (pen.x + (float)ch_info.region.size.width
                > r.size.width + r.origin.x) {
                pen.x = r.origin.x;
                pen.y += font_->line_height();
            }

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