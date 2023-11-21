#include <niu2x/gfx/gui/button.h>
#include <niu2x/gfx/resource_manager.h>

namespace niu2x::gfx::gui {

Button::Button()
{
    set_justify_content(Justify::center);
    set_align_items(Align::center);

    auto res_mgr = ResourceManager::get();

    auto bg = make_unique<Image>();
    bg->set_image("image/ui-pack", "blue_button00.png");

    bg->set_justify_content(Justify::center);
    bg->set_align_items(Align::center);

    bg_ = bg.get();
    add_child(move(bg));

    auto font = res_mgr->get_font("font/normal");
    auto text = make_unique<Text>();
    text->set_font(font);
    text_ = text.get();
    bg_->add_child(move(text));

    text_->set_margin(8);
}

Button::~Button() { }

void Button::update_canvas() { }

void Button::set_text(const String& sz) { text_->set_text(sz); }

} // namespace niu2x::gfx::gui