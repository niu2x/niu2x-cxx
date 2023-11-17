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

    auto program
        = ResourceManager::get()->get_render_program(RenderProgramID::TEXT);
    auto maybe = string_utils::utf8_to_utf32(text_);
    if (maybe) {
        font_->prepare(*maybe);
        for (auto ch : *maybe) {
            auto& ch_info = font_->get_char_info(ch);
            auto tex = font_->get_texture(ch_info.tex);
            c->add_image(ImageSheet::Frame(tex, ch_info.region), r, program);
        }
    }
}

} // namespace niu2x::gfx::gui