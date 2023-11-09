#ifndef NIU2X_GFX_RENDER_COMMAND_H
#define NIU2X_GFX_RENDER_COMMAND_H

#include <memory_resource>
#include <niu2x/singleton.h>
#include <niu2x/type/std_alias.h>
#include <niu2x/math/geometry.h>
#include <niu2x/math/linalg_alias.h>
#include <niu2x/gfx/hardward_resource.h>
#include <niu2x/gfx/image_sheet.h>

namespace niu2x::gfx {

using Rect = math::Rect<float>;
using UniformPacket = RenderProgram::UniformPacket;

static const Mat4 unit_mat4 { { 1, 0, 0, 0 }, { 0, 1, 0, 0 }, { 0, 0, 1, 0 },
    { 0, 0, 0, 1 } };

class RenderCommand {
public:
    virtual ~RenderCommand() = 0;
    virtual void run() = 0;
};

} // namespace niu2x::gfx

namespace niu2x::gfx::render_command {

class Clear : public RenderCommand {
public:
    Clear();
    ~Clear();
    void run() override;
};

class Triangles : public RenderCommand {
public:
    Triangles() { }
    ~Triangles() { }

    void set_vbo(VertexBuffer* vbo) { vbo_ = vbo; }
    void set_veo(IndexBuffer* veo) { veo_ = veo; }
    void set_program(RenderProgram* p) { program_ = p; }
    void set_uniforms(UniformPacket* uf) { uniforms_ = uf; }
    void set_texture(Index i, Texture2D* tex) { textures_[i] = tex; }

    void run() override;

private:
    IndexBuffer* veo_ = nullptr;
    VertexBuffer* vbo_ = nullptr;
    RenderProgram* program_ = nullptr;
    UniformPacket* uniforms_ = nullptr;
    Array<Texture2D*, 8> textures_ = { { nullptr } };
};

} // namespace niu2x::gfx::render_command

#endif