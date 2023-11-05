#ifndef NIU2X_GFX_RENDER_COMMAND_H
#define NIU2X_GFX_RENDER_COMMAND_H

#include <memory_resource>
#include <niu2x/singleton.h>
#include <niu2x/type/std_alias.h>
#include <niu2x/math/geometry.h>
#include <niu2x/math/linalg_alias.h>
#include <niu2x/gfx/hardward_resource.h>

namespace niu2x::gfx {

using Rect = math::Rect<float>;

struct Color {
    float r, g, b, a;
};

static const Mat4 unit_mat4 { { 1, 0, 0, 0 }, { 0, 1, 0, 0 }, { 0, 0, 1, 0 },
    { 0, 0, 0, 1 } };

class RenderCommand {
public:
    virtual ~RenderCommand() = 0;
    virtual void run() = 0;
};

} // namespace niu2x::gfx

namespace niu2x::gfx {

using UniformPacket = RenderProgram::UniformPacket;

class RenderCommandFactory : public Singleton<RenderCommandFactory> {
public:
    using PolyAlloctor = std::pmr::polymorphic_allocator<uint8_t>;

    RenderCommandFactory();

    void destroy(RenderCommand*);

    RenderCommand* create_clear();

    RenderCommand* create_triangles(
        VertexBuffer* vb, RenderProgramID program_id, UniformPacket&& uniforms);

    RenderCommand* create_triangles(VertexBuffer* vb,
        RenderProgramID program_id, const UniformPacket& uniforms);

    RenderCommand* create_rect(const Rect& rect, const Color& color);

private:
    std::pmr::unsynchronized_pool_resource memory_;

    PolyAlloctor alloctor_;
};

} // namespace niu2x::gfx

namespace niu2x::gfx::render_command {

class Clear : public RenderCommand {
public:
    Clear();
    ~Clear();
    void run() override;
};

class DrawRect : public RenderCommand {
public:
    DrawRect(const Rect& rect, const Color& color);
    ~DrawRect();
    void run() override;

private:
    Rect rect_;
    Color color_;
};

class Triangles : public RenderCommand {
public:
    Triangles(
        VertexBuffer* vb, RenderProgramID program_id, UniformPacket&& uniforms)
    : vb_(vb)
    , program_id_(program_id)
    , uniforms_(move(uniforms))
    {
    }
    Triangles(VertexBuffer* vb, RenderProgramID program_id,
        const UniformPacket& uniforms)
    : vb_(vb)
    , program_id_(program_id)
    , uniforms_(uniforms)
    {
    }
    ~Triangles() { }

    void run() override;

private:
    VertexBuffer* vb_;
    RenderProgramID program_id_;
    UniformPacket uniforms_;
};

} // namespace niu2x::gfx::render_command

#endif