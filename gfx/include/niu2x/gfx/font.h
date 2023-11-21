#ifndef NIU2X_GFX_FONT_H
#define NIU2X_GFX_FONT_H

#include <niu2x/type/std_alias.h>
#include <niu2x/noncopyable.h>
#include <niu2x/fs.h>
#include <niu2x/gfx/hardward_resource.h>
#include <niu2x/image/image_data.h>

#include <freetype2/ft2build.h>
#include FT_FREETYPE_H
#include FT_STROKER_H

namespace niu2x::gfx {

class FontLibrary : private Noncopyable {
public:
    FontLibrary();
    ~FontLibrary();
    FT_Library get();
};

class Font : private Noncopyable {
public:
    Font(const fs::Path& ttf, int font_size);
    ~Font();

    struct CharInfo {
        Index tex;
        Index chr_index;
        IntRect region;
        int x_offset;
        int y_offset;
        int x_advance;
    };

    void prepare(char32_t ch);
    void prepare(const String32& sz);

    int line_height() const { return line_height_; }

    bool chr_exist(char32_t ch) const;

    void pushback_glyph(
        char32_t ch,
        const CharInfo& info,
        const image::ImageData& glyph);

    Texture2D* get_texture(Index page) const { return textures_[page].get(); }

    const CharInfo& get_char_info(char32_t ch) const { return charmap_.at(ch); }

    int font_size() const { return font_size_; }
    int baseline() const { return baseline_; }

private:
    fs::Path ttf_path_;
    int font_size_;
    int baseline_;

    Vector<UniquePtr<Texture2D>> textures_;
    HashMap<char32_t, CharInfo> charmap_;

    Index page_ = 0;
    Index count_ = 0;
    const NR max_count_;

    FT_Face face_ = nullptr;
    Buffer ttf_data_;

    FontLibrary lib_;
    int line_height_ = 0;

    Texture2D* get_or_create_tex(Index page);

    IntRect chr_index_to_region(Index i);
};

} // namespace niu2x::gfx

#endif