#ifndef NIU2X_GFX_GUI_IMAGE_H
#define NIU2X_GFX_GUI_IMAGE_H

#include <niu2x/gfx/gui/node.h>
// #include <niu2x/gfx/resource_manager.h>

namespace niu2x::gfx {
using ResId = String;
}

namespace niu2x::gfx::gui {

class Image : public Node {
public:
    Image();
    ~Image();

    void update_canvas() override;
    void set_image(const ResId& sheet, const String& name);
    void set_image(ImageSheet::Frame* frame);

    math::Size<float> measure(const SizeRange& size_range) override;

private:
    ImageSheet::Frame* image_ = nullptr;
};

} // namespace niu2x::gfx::gui

#endif
