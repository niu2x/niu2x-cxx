#ifndef NIU2X_GFX_GUI_CANVAS_H
#define NIU2X_GFX_GUI_CANVAS_H

#include <niu2x/gfx/gui/node.h>

namespace niu2x::gfx::gui {

class Canvas : public Node {
public:
    ~Canvas();
    void draw();
};

} // namespace niu2x::gfx::gui

#endif
