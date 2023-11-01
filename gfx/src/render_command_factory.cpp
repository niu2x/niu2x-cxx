#include <niu2x/gfx/render_command.h>

namespace niu2x::gfx {

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

void RenderCommandFactory::destroy(RenderCommand* obj)
{
    alloctor_.delete_object(obj);
}

} // namespace niu2x::gfx
