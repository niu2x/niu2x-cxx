#include <niu2x/gfx/render_command.h>

namespace niu2x::gfx {

namespace rc = render_command;
using Factory = RenderCommandFactory;
using CMD = Factory::CMD;
using UniPacket = UniformPacket;

Factory::RenderCommandFactory()

: memory_({
    .max_blocks_per_chunk = 256,
    .largest_required_pool_block = 512,
})
, alloctor_(&memory_)
{
}

CMD* Factory::create_clear() { return alloctor_.new_object<rc::Clear>(); }

CMD* Factory::create_triangles(VBO* vb, ProgramID pid, UniPacket&& uniforms)
{
    return alloctor_.new_object<rc::Triangles>(vb, pid, move(uniforms));
}

CMD* Factory::create_triangles(VBO* vb, ProgramID pid, CR<UniPacket> uniforms)
{
    return alloctor_.new_object<rc::Triangles>(vb, pid, uniforms);
}

CMD* Factory::create_rect(const Rect& rect, const Color& color)
{
    return alloctor_.new_object<rc::DrawRect>(rect, color);
}

void Factory::destroy(CMD* obj) { alloctor_.delete_object(obj); }

CMD* Factory::create_ui(const Rect& rect, ImageSheet::Frame* frame)
{
    return alloctor_.new_object<rc::DrawUI>(rect, frame);
}

CMD* Factory::create_ui(VertexBuffer* vbo, ImageSheet::Frame* frame)
{
    return alloctor_.new_object<rc::DrawUI>(vbo, frame);
}

} // namespace niu2x::gfx
