#include <niu2x/gfx/render_command.h>
#include <niu2x/type/std_alias.h>

namespace niu2x::gfx {

// using Factory = RenderCommandFactory;
// using CMD = Factory::CMD;
// using UniPacket = UniformPacket;

// Factory::RenderCommandFactory()

// : memory_({
//     .max_blocks_per_chunk = 256,
//     .largest_required_pool_block = 512,
// })
// , alloctor_(&memory_)
// {
// }

// CMD* Factory::create_clear() { return alloctor_.new_object<rc::Clear>(); }

// CMD* Factory::create_triangles(VBO* vb, ProgramID pid, UniPacket&& uniforms)
// {
//     rc::Triangles::InitParam init_param { vb, nullptr, pid, move(uniforms) };
//     return alloctor_.new_object<rc::Triangles>(move(init_param));
// }

// CMD* Factory::create_triangles(VBO* vb, ProgramID pid, CR<UniPacket>
// uniforms)
// {
//     rc::Triangles::InitParam init_param { vb, nullptr, pid, uniforms };
//     return alloctor_.new_object<rc::Triangles>(move(init_param));
// }

// CMD* Factory::create_triangles(rc::Triangles::InitParam&& param)
// {
//     return alloctor_.new_object<rc::Triangles>(move(param));
// }

// void Factory::destroy(CMD* obj) { alloctor_.delete_object(obj); }

} // namespace niu2x::gfx
