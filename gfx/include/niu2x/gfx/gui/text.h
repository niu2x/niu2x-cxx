#ifndef NIU2X_GFX_GUI_TEXT_H
#define NIU2X_GFX_GUI_TEXT_H

#include <niu2x/gfx/gui/node.h>
#include <niu2x/gfx/font.h>

namespace niu2x::gfx::gui {

class Text : public Node {
public:
    Text();
    ~Text();
    void update_canvas() override;

    void set_font(Font* fnt)
    {
        font_ = fnt;
        set_dirty();
    }
    void set_text(const String& sz)
    {
        text_ = sz;
        set_dirty();
    }

private:
    String text_;
    Font* font_ = nullptr;
};

} // namespace niu2x::gfx::gui

#endif
