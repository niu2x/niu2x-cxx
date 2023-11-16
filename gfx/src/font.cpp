#include <niu2x/gfx/font.h>

namespace niu2x::gfx {

Font::Font(const fs::Path& ttf, int font_size)
: ttf_path_(ttf)
, font_size_(font_size)
{
}

} // namespace niu2x::gfx