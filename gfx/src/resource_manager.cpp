#include <yaml-cpp/yaml.h>

#include <niu2x/unused.h>
#include <niu2x/gfx/resource_manager.h>
#include <niu2x/gfx/gfx_factory.h>
#include <niu2x/fs.h>
#include <niu2x/stream.h>
#include <iostream>

namespace niu2x::gfx {

ResourceManager::ResourceManager() { }

void ResourceManager::load_texture2d(
    const ResId& id, const Path& path, PixelFormat format)
{
    auto tex = GFX_Factory::get()->create_texture2d();

    fs::File png_file(path);
    stream::FileReadStream png_in(png_file);

    tex->load(&png_in, format);
    texture2ds_[id] = std::move(tex);
}

static const HashMap<String, PixelFormat> pixel_format_map {
    { "rgba_8888", PixelFormat::RGBA_8888 },
    { "rgb_888", PixelFormat::RGB_888 },
};

void ResourceManager::load_texture2d(const Path& path)
{
    fs::File config_file(path);
    auto config_buffer = config_file.as_buffer(true);
    YAML::Node config
        = YAML::Load(reinterpret_cast<const char*>(config_buffer.data()));
    auto sz_pixel_format = config["pixel_format"].as<String>();
    auto pixel_format = pixel_format_map.at(sz_pixel_format);
    auto image_path = config_file.parent().path() / config["path"].as<String>();
    return load_texture2d(path, image_path, pixel_format);
}

void ResourceManager::clear() { texture2ds_.clear(); }

} // namespace niu2x::gfx