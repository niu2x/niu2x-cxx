#include <niu2x/gfx/gui/panel.h>
#include <niu2x/gfx/resource_manager.h>

namespace niu2x::gfx::gui {
Panel::Panel() { }
Panel::~Panel() { }

void Panel::update_canvas()
{
    auto c = canvas();

    c->clear();

    auto r = compute_self_rect();
    if (r.size.area() <= 0)
        return;

    c->add_image(
        background_
            ?: ResourceManager::get()->get_image_sheet_frame(
                "ui-pack",
                "blue_panel.png"),
        r);
}

void Panel::set_background(const ResId& sheet, const String& name)
{
    background_ = ResourceManager::get()->get_image_sheet_frame(sheet, name);
}

} // namespace niu2x::gfx::gui