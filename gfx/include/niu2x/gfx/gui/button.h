#ifndef NIU2X_GFX_GUI_BUTTON_H
#define NIU2X_GFX_GUI_BUTTON_H

#include <niu2x/gfx/gui/node.h>
#include <niu2x/gfx/gui/text.h>
#include <niu2x/gfx/font.h>

namespace niu2x::gfx::gui {

class Button : public Node {
public:
    Button();
    ~Button();
    void update_canvas() override;

private:
    // Image
};

} // namespace niu2x::gfx::gui

#endif
