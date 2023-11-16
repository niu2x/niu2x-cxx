#include <ft2build.h>
#include FT_FREETYPE_H
#include FT_STROKER_H

#include <atomic>
#include <niu2x/gfx/gui/text.h>
#include <niu2x/string_utils.h>

namespace niu2x::gfx::gui {

static std::atomic<int> freetype_refcount { 0 };
static FT_Library freetype;

static void freetype_get()
{
    if (++freetype_refcount == 1) {
        FT_Init_FreeType(&freetype);
    }
}

static void freetype_put()
{
    if (--freetype_refcount == 0) {
        FT_Done_FreeType(freetype);
    }
}

Text::Text() { freetype_get(); }

Text::~Text() { freetype_put(); }

void Text::update_canvas()
{
    // auto c = canvas();
    auto maybe = string_utils::utf8_to_utf32(text_);
    if (maybe) {
        for (auto ch : *maybe) {
            printf("ch: %d\n", ch);
        }
    }
}

} // namespace niu2x::gfx::gui