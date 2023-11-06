#include <niu2x/gfx/image_sheet.h>
#include <niu2x/fs/file.h>
#include <pugixml.hpp>

namespace niu2x::gfx {

ImageSheet::ImageSheet() { }

void ImageSheet::add_page(UniquePtr<Texture2D> tex, CR<fs::Path>& sub_config)
{

    fs::File config_file(sub_config);
    auto config_buffer = config_file.as_buffer(true);
    auto config_data = reinterpret_cast<const char*>(config_buffer.data());

    pugi::xml_document doc;
    auto result = doc.load_string(config_data);
    if (!result) {
        throw_runtime_err(result.description());
    }

    auto item = doc.child("TextureAtlas").child("SubTexture");
    while (item) {
        auto name = item.attribute("name").as_string();
        auto x = item.attribute("x").as_int();
        auto y = item.attribute("y").as_int();
        auto width = item.attribute("width").as_int();
        auto height = item.attribute("height").as_int();

        Frame frame(tex.get(), { x, y, width, height });
        frames_[String(name)] = frame;

        item = item.next_sibling("SubTexture");
    }

    textures_.push_back(move(tex));
}

} // namespace niu2x::gfx