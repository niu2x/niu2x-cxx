#ifndef NIU2X_GFX_RESOURCE_MANAGER_H
#define NIU2X_GFX_RESOURCE_MANAGER_H

#include <niu2x/singleton.h>
#include <niu2x/gfx/hardward_resource.h>
#include <niu2x/fs/path.h>
#include <niu2x/gfx/image_sheet.h>

namespace niu2x::gfx {

using Path = fs::Path;
using ResId = String;

class ResourceManager : public Singleton<ResourceManager> {
public:
    ResourceManager();

    void clear();

    void load_texture2d(const Path& path);
    void load_texture2d(const ResId& id, const Path& path, PixelFormat format);

    void load_vertex_buffer(const ResId& id, const Path& path);
    void load_vertex_buffer(const Path& path) { load_vertex_buffer("", path); }

    void load_render_program(RenderProgramID id);

    void load_image_sheet(const Path& path);

#define GET(type, name, ResIdType)                                             \
    inline type* get_##name(const ResIdType& id) const                         \
    {                                                                          \
        return name##s_.at(id).get();                                          \
    }

    GET(Texture2D, texture2d, ResId);
    GET(VertexBuffer, vertex_buffer, ResId);
    GET(RenderProgram, render_program, RenderProgramID);
    GET(ImageSheet, image_sheet, ResId);

    ImageSheet::Frame* get_image_sheet_frame(
        CR<ResId> id, CR<String> sub_name) const
    {
        return get_image_sheet(id)->get_frame(sub_name);
    }

private:
    HashMap<ResId, UPtr<Texture2D>> texture2ds_;
    HashMap<ResId, UPtr<VertexBuffer>> vertex_buffers_;
    HashMap<RenderProgramID, UPtr<RenderProgram>> render_programs_;
    HashMap<ResId, UPtr<ImageSheet>> image_sheets_;

    UPtr<Texture2D> _load_texture2d(const Path& path, PixelFormat format);
};

} // namespace niu2x::gfx

#endif