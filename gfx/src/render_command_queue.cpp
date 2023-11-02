#include <niu2x/gfx/render_command_queue.h>

namespace niu2x::gfx {

RenderCommandQueue::RenderCommandQueue() { }

void RenderCommandQueue::enqueue(RenderCommand* cmd)
{
    commands_.push_back(cmd);
}

void RenderCommandQueue::render()
{
    auto factory = RenderCommandFactory::get();

    for (auto x : commands_) {
        x->run();
        factory->destroy(x);
    }

    commands_.clear();
}

} // namespace niu2x::gfx