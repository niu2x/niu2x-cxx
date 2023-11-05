#include <niu2x/gfx/render_command.h>

namespace niu2x::gfx {

namespace rc = render_command;

RenderCommandFactory::RenderCommandFactory()

: memory_({
    .max_blocks_per_chunk = 256,
    .largest_required_pool_block = 512,
})
, alloctor_(&memory_)
{
}

RenderCommand* RenderCommandFactory::create_clear()
{
    return alloctor_.new_object<rc::Clear>();
}

RenderCommand* RenderCommandFactory::create_triangles(
    VertexBuffer* vb, RenderProgramID program_id, UniformPacket&& uniforms)
{
    return alloctor_.new_object<rc::Triangles>(vb, program_id, move(uniforms));
}

RenderCommand* RenderCommandFactory::create_triangles(
    VertexBuffer* vb, RenderProgramID program_id, const UniformPacket& uniforms)
{
    return alloctor_.new_object<rc::Triangles>(vb, program_id, uniforms);
}

RenderCommand* RenderCommandFactory::create_rect(
    const Rect& rect, const Color& color)
{
    return alloctor_.new_object<rc::DrawRect>(rect, color);
}

void RenderCommandFactory::destroy(RenderCommand* obj)
{
    alloctor_.delete_object(obj);
}

} // namespace niu2x::gfx
