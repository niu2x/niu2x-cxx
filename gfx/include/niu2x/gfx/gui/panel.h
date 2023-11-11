#ifndef NIU2X_GFX_GUI_PANEL_H
#define NIU2X_GFX_GUI_PANEL_H

#include <niu2x/gfx/gui/node.h>

namespace niu2x::gfx::gui {

class Panel : public Node {
public:
    Panel();
    ~Panel();

    void update_canvas() override;
};

} // namespace niu2x::gfx::gui

#endif
