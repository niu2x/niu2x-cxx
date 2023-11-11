#include <niu2x/gfx/gui/panel.h>
#include <niu2x/gfx/resource_manager.h>

namespace niu2x::gfx::gui {
Panel::Panel() { }
Panel::~Panel() { }

void Panel::update_canvas()
{
    auto c = canvas();

    c->clear();

    c->add_image(
        ResourceManager::get()->get_image_sheet_frame(
            "ui-pack", "blue_panel.png"),
        compute_self_rect());
}
} // namespace niu2x::gfx::gui