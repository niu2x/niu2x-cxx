#include <atomic>
#include <niu2x/gfx/gui/text.h>
#include <niu2x/string_utils.h>

namespace niu2x::gfx::gui {

Text::Text() { }

Text::~Text() { }

void Text::update_canvas()
{
    // auto c = canvas();
    auto maybe = string_utils::utf8_to_utf32(text_);
    if (maybe) {
        font_->prepare(*maybe);
    }
}

} // namespace niu2x::gfx::gui