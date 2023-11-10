#include <yaml-cpp/yaml.h>

#include <niu2x/unused.h>
#include <niu2x/gfx/resource_manager.h>
#include <niu2x/gfx/gfx_factory.h>
#include <niu2x/fs.h>
#include <niu2x/stream.h>
#include <iostream>

namespace niu2x::gfx {

ResourceManager::ResourceManager() { }

static ResId get_id(const ResId& id, const Path& path, const YAML::Node& config)
{
    if (id != "")
        return id;

    if (config.IsMap()) {
        if (const auto& id_node = config["id"]) {
            return id_node.as<String>();
        }
    }

    return path;
}

UPtr<Texture2D> ResourceManager::_load_texture2d(CR<Path> path, PixelFmt fmt)
{
    auto tex = GFX_Factory::get()->create_texture2d();
    fs::File png_file(path);
    stream::FileReadStream png_in(png_file);
    tex->load(&png_in, fmt);
    return tex;
}

void ResourceManager::load_texture2d(CR<ResId> id, CR<Path> path, PixelFmt f)
{
    texture2ds_[id] = _load_texture2d(path, f);
}

static const HashMap<String, PixelFmt> pixel_format_map {
    { "rgba_8888", PixelFmt::RGBA_8888 },
    { "rgb_888", PixelFmt::RGB_888 },
};

static YAML::Node load_yaml(const Path& path)
{
    fs::File config_file(path);
    auto config_buffer = config_file.as_buffer(true);
    auto config_data = reinterpret_cast<const char*>(config_buffer.data());
    YAML::Node config = YAML::Load(config_data);
    return config;
}

void ResourceManager::load_texture2d(const Path& path)
{
    YAML::Node config = load_yaml(path);
    auto sz_pixel_format = config["pixel_format"].as<String>();
    auto pixel_format = pixel_format_map.at(sz_pixel_format);
    auto image_path = path.abs().parent() / config["path"].as<String>();
    return load_texture2d(get_id("", path, config), image_path, pixel_format);
}

void ResourceManager::clear()
{
    texture2ds_.clear();
    vertex_buffers_.clear();
    render_programs_.clear();
    image_sheets_.clear();
}

void ResourceManager::load_render_program(RenderProgramID id)
{
    render_programs_[id] = gfx::GFX_Factory::get()->create_render_program(id);
}

void ResourceManager::load_vertex_buffer(const ResId& id, const Path& path)
{
    YAML::Node config = load_yaml(path);
    auto vertex_count = config["position"].size();

    auto vb = GFX_Factory::get()->create_vertex_buffer();
    vb->resize(vertex_count);

    Vector<Vertex> vertexs;
    vertexs.resize(vertex_count);
    Index i = 0;

    for (const auto& vertex : config["position"]) {
        float x = vertex[0].as<float>();
        float y = vertex[1].as<float>();
        float z = vertex[2].as<float>();

        vertexs[i].x = x;
        vertexs[i].y = y;
        vertexs[i++].z = z;
    }

    i = 0;

    for (const auto& vertex : config["color"]) {
        float r = vertex[0].as<float>();
        float g = vertex[1].as<float>();
        float b = vertex[2].as<float>();
        float a = vertex[3].as<float>();

        vertexs[i].r = r;
        vertexs[i].g = g;
        vertexs[i].b = b;
        vertexs[i++].a = a;
    }

    i = 0;

    for (const auto& vertex : config["uv"]) {
        float u = vertex[0].as<float>();
        float v = vertex[1].as<float>();
        vertexs[i].u = u;
        vertexs[i++].v = v;
    }

    vb->set_vertexs(0, vertex_count, vertexs.data());
    vertex_buffers_[get_id(id, path, config)] = move(vb);
}

void ResourceManager::load_image_sheet(const Path& path)
{
    YAML::Node config = load_yaml(path);

    auto image_sheet = make_unique<ImageSheet>();

    auto sz_pixel_fmt = config["pixel_format"].as<String>();
    auto pixel_fmt = pixel_format_map.at(sz_pixel_fmt);

    auto root = path.abs().parent();
    for (const auto& sheet : config["pages"]) {
        auto sub = root / sheet["sub"].as<String>();
        auto image = root / sheet["image"].as<String>();
        image_sheet->add_page(_load_texture2d(image, pixel_fmt), sub);
    }

    auto id = get_id("", path, config);
    image_sheets_[id] = move(image_sheet);
}

} // namespace niu2x::gfx