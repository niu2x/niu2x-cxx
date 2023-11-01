#ifndef NIU2X_GFX_RENDER_QUEUE_H
#define NIU2X_GFX_RENDER_QUEUE_H

#include <niu2x/singleton.h>
#include <niu2x/type/std_alias.h>
#include <niu2x/gfx/render_command.h>

namespace niu2x::gfx {

class RenderCommandQueue : public Singleton<RenderCommandQueue> {
public:
    RenderCommandQueue();
    void enqueue(RenderCommand* cmd);
    void render();

private:
    Vector<RenderCommand*> commands_;
};

} // namespace niu2x::gfx

#endif