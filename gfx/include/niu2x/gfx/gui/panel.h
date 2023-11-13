#ifndef NIU2X_GFX_GUI_PANEL_H
#define NIU2X_GFX_GUI_PANEL_H

#include <niu2x/gfx/gui/node.h>
// #include <niu2x/gfx/resource_manager.h>

namespace niu2x::gfx {
using ResId = String;
}

namespace niu2x::gfx::gui {

class Panel : public Node {
public:
    Panel();
    ~Panel();

    void update_canvas() override;
    void set_background(const ResId& sheet, const String& name);

private:
    ImageSheet::Frame* background_ = nullptr;
};

} // namespace niu2x::gfx::gui

#endif
