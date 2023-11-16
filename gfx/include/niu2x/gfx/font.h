#ifndef NIU2X_GFX_FONT_H
#define NIU2X_GFX_FONT_H

#include <niu2x/type/std_alias.h>
#include <niu2x/noncopyable.h>
#include <niu2x/fs.h>

namespace niu2x::gfx {

class Font : private Noncopyable {
public:
    Font(const fs::Path& ttf, int font_size);

private:
    fs::Path ttf_path_;
    int font_size_;
};

} // namespace niu2x::gfx

#endif