#ifndef NIU2X_GFX_GUI_CANVAS_H
#define NIU2X_GFX_GUI_CANVAS_H

#include <niu2x/noncopyable.h>
#include <niu2x/gfx/hardward_resource.h>

namespace niu2x::gfx::gui {

using Rect = math::Rect<float>;

class Canvas : private Noncopyable {
public:
    Canvas();
    ~Canvas();
    void draw();
    void add_rect(const Rect&);

private:
    struct RectCommand {
        Rect rect;
    };

    using Command = Variant<RectCommand>;
    Vector<Command> commands_;
};

} // namespace niu2x::gfx::gui

#endif