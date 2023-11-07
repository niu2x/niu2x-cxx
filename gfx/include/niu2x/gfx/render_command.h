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

class DrawRect : public RenderCommand {
public:
    DrawRect(const Rect& rect, const Color& color);
    ~DrawRect();
    void run() override;

private:
    Rect rect_;
    Color color_;
};

class DrawUI : public RenderCommand {
public:
    DrawUI(const Rect& rect, ImageSheet::Frame* frame);
    DrawUI(VertexBuffer* vbo, ImageSheet::Frame* frame, bool scale9 = false);
    DrawUI(
        VertexBuffer* vbo, IndexBuffer* veo, ImageSheet::Frame* frame,
        bool scale9 = false);
    ~DrawUI();
    void run() override;

private:
    Rect rect_;
    VertexBuffer* vbo_ = nullptr;
    IndexBuffer* veo_ = nullptr;
    ImageSheet::Frame* frame_ = nullptr;
    bool scale9_ = false;
};

class Triangles : public RenderCommand {
public:
    struct InitParam {
        VertexBuffer* vbo;
        IndexBuffer* veo;
        RenderProgramID program_id;
        UniformPacket uniforms;
    };

    Triangles(InitParam&& p)
    : veo_(p.veo)
    , vbo_(p.vbo)
    , program_id_(p.program_id)
    , uniforms_(move(p.uniforms))
    {
    }

    ~Triangles() { }

    void run() override;

private:
    IndexBuffer* veo_;
    VertexBuffer* vbo_;
    RenderProgramID program_id_;
    UniformPacket uniforms_;
};

} // namespace niu2x::gfx::render_command

namespace niu2x::gfx {
namespace rc = render_command;

class RenderCommandFactory : public Singleton<RenderCommandFactory> {
public:
    using PolyAlloctor = std::pmr::polymorphic_allocator<uint8_t>;
    using ProgramID = RenderProgramID;
    using VBO = VertexBuffer;
    using VEO = IndexBuffer;
    using CMD = RenderCommand;

    RenderCommandFactory();

    void destroy(CMD*);

    CMD* create_clear();

    CMD* create_triangles(VBO* vb, ProgramID pid, UniformPacket&& uniforms);
    CMD* create_triangles(VBO* vb, ProgramID pid, CR<UniformPacket> uniforms);
    CMD* create_triangles(rc::Triangles::InitParam&& param);

    CMD* create_rect(const Rect& rect, const Color& color);

    CMD* create_ui(const Rect& rect, ImageSheet::Frame* frame);
    CMD* create_ui(VertexBuffer* vbo, ImageSheet::Frame* frame);
    CMD*
    create_ui(VertexBuffer* vbo, IndexBuffer* veo, ImageSheet::Frame* frame);

private:
    std::pmr::unsynchronized_pool_resource memory_;

    PolyAlloctor alloctor_;
};

} // namespace niu2x::gfx

#endif