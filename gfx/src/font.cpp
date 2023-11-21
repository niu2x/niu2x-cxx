#include <niu2x/gfx/font.h>
#include <niu2x/stream.h>
#include <niu2x/unused.h>
#include <niu2x/gfx/gfx_factory.h>

#define TO_POINT(p) ((int)(64.f * (p)))
#define PADDING     (8)

namespace niu2x::gfx {

static std::atomic<int> freetype_refcount { 0 };
static FT_Library freetype;

FontLibrary::FontLibrary()
{
    if (++freetype_refcount == 1) {
        FT_Init_FreeType(&freetype);
    }
}

FontLibrary::~FontLibrary()
{
    if (--freetype_refcount == 0) {
        FT_Done_FreeType(freetype);
    }
}

FT_Library FontLibrary::get() { return freetype; }

Font::Font(const fs::Path& ttf, int font_size)
: ttf_path_(ttf)
, font_size_(font_size)
, max_count_(
      (2048 / (font_size_ + (PADDING << 1)))
      * (2048 / (font_size_ + (PADDING << 1))))
{
    fs::File ttf_file(ttf_path_);
    stream::FileReadStream ttf_in(ttf_file);
    stream::BufferWriteStream file_content_writer;
    pipe(&ttf_in, &file_content_writer);
    ttf_data_ = file_content_writer.move_buffer();

    if (FT_New_Memory_Face(
            lib_.get(),
            ttf_data_.data(),
            ttf_data_.size(),
            0,
            &face_)) {
        throw_runtime_err("load ttf fail");
    }
}

Font::~Font() { FT_Done_Face(face_); }

static image::ImageData rasterize_bitmap(FT_Bitmap bitmap)
{
    image::ImageData image_data;
    image_data.reset(bitmap.width, bitmap.rows, 3);

    if (image_data.size().area() > 0) {

        switch (bitmap.pixel_mode) {
            case FT_PIXEL_MODE_GRAY: {
                auto* ptr = image_data.data();
                for (int y = 0; y < image_data.size().height; y++) {
                    for (int x = 0; x < image_data.size().width; x++) {
                        *ptr++ = bitmap.buffer[y * bitmap.pitch + x];
                        *ptr++ = bitmap.buffer[y * bitmap.pitch + x];
                        *ptr++ = bitmap.buffer[y * bitmap.pitch + x];
                    }
                }
                break;
            }
            default: {
                image_data.reset(0, 0, 3);
            }
        }
    }
    return image_data;
}

void Font::prepare(char32_t ch)
{
    if (chr_exist(ch))
        return;

    CharInfo info;

    info.x_advance = 0;
    info.region = {
        0,
        0,
        0,
        0,
    };

    int hinting = FT_LOAD_TARGET_NORMAL;
    int flags = FT_LOAD_DEFAULT | hinting;

    int32_t glyph_index = FT_Get_Char_Index(face_, ch);
    if (FT_Load_Glyph(face_, glyph_index, flags))
        return;

    info.x_advance = (static_cast<int>(face_->glyph->metrics.horiAdvance >> 6));

    FT_GlyphSlot slot = face_->glyph;
    if (FT_Render_Glyph(slot, FT_RENDER_MODE_NORMAL))
        return;

    FT_Bitmap bitmap = slot->bitmap;
    auto glyph = rasterize_bitmap(bitmap);

    // printf("slot->metrics.horiBearingX %ld\n", slot->metrics.horiBearingX);
    // printf("slot->bitmap_left %d\n", slot->bitmap_left);

    info.x_offset = slot->metrics.horiBearingX >> 6;
    info.y_offset = -(slot->metrics.horiBearingY >> 6);

    if (glyph.size().area() > 0) {
        pushback_glyph(ch, info, glyph);
    }
}

IntRect Font::chr_index_to_region(Index i)
{
    int cell_size = (font_size_ + (PADDING << 1));
    NR nr_per_line = (2048 / cell_size);
    Index x = i % nr_per_line;
    Index y = i / nr_per_line;

    return {
        (int)(x * cell_size),
        (int)(y * cell_size),
        cell_size,
        cell_size,
    };
}

void Font::pushback_glyph(
    char32_t ch,
    const CharInfo& p_info,
    const image::ImageData& glyph)
{
    CharInfo info = p_info;
    info.chr_index = count_++;
    info.tex = page_;

    if (count_ >= max_count_) {
        page_++;
        count_ = 0;
    }

    auto texture = get_or_create_tex(info.tex);
    auto region = chr_index_to_region(info.chr_index);
    region.size = glyph.size();
    texture->set_data(region, glyph.data());
    info.region = region;
    charmap_[ch] = info;
}

Texture2D* Font::get_or_create_tex(Index page)
{
    if (page < textures_.size()) {
        return textures_[page].get();
    }

    auto new_tex = GFX_Factory::get()->create_texture2d();
    new_tex->resize({ 2048, 2048 }, PixelFormat::RGB_888);
    textures_.push_back(move(new_tex));

    return get_or_create_tex(page);
}

bool Font::chr_exist(char32_t ch) const
{
    return charmap_.find(ch) != charmap_.end();
}

void Font::prepare(const String32& sz)
{

    if (FT_Select_Charmap(face_, FT_ENCODING_UNICODE)) {
        // Maybe<int> found  ;
        // for (int i = 0; i < face_->num_charmaps;
        //      i++) {
        //     if (face_->charmaps[i]->encoding != FT_ENCODING_NONE) {
        //         found = i;
        //         break;
        //     }
        // }

        // if (!found ) {
        //     return;
        // }

        // auto encoding = face_->charmaps[*found]->encoding;
        // if (FT_Select_Charmap(face_, encoding)) {
        //     return ;
        // }
        return;
    }

    const int dpi = 72;
    int fnt_size = TO_POINT(font_size_);
    if (FT_Set_Char_Size(face_, fnt_size, fnt_size, dpi, dpi))
        return;

    line_height_ = static_cast<int>(
        (face_->size->metrics.ascender - face_->size->metrics.descender) >> 6);

    baseline_ = face_->size->metrics.descender >> 6;

    for (auto ch : sz) {
        prepare(ch);
    }
}

} // namespace niu2x::gfx