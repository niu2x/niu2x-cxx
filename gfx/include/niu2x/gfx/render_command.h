#ifndef NIU2X_GFX_RENDER_COMMAND_H
#define NIU2X_GFX_RENDER_COMMAND_H

#include <memory_resource>
#include <niu2x/singleton.h>
#include <niu2x/type/std_alias.h>
#include <niu2x/math/geometry.h>
#include <niu2x/gfx/hardward_resource.h>

namespace niu2x::gfx {

using Rect = math::Rect<float>;

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
    DrawRect();
    ~DrawRect();
    void run() override;

private:
    Rect rect_;
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