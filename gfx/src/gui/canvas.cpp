#include <niu2x/gfx/gui/canvas.h>
#include <niu2x/gfx/render_command_queue.h>
#include <niu2x/gfx/render_command.h>

namespace niu2x::gfx::gui {

Canvas::Canvas() { }

Canvas::~Canvas() { }

void Canvas::draw()
{
    auto rcf = RenderCommandFactory::get();
    auto rq = RenderCommandQueue::get();

    for (auto& c : commands_) {
        std::visit(
            [rcf, rq](auto& arg) {
                using T = decay<decltype(arg)>;
                if constexpr (is_same<T, RectCommand>) {
                    auto render_cmd
                        = rcf->create_rect(arg.rect, { 0, 0, 0, 0.1 });
                    rq->enqueue(render_cmd);
                }
            },
            c);
    }
}

void Canvas::add_rect(const Rect& r)
{
    RectCommand cmd { r };
    commands_.emplace_back(cmd);
}

} // namespace niu2x::gfx::gui