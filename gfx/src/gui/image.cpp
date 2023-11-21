#include <niu2x/gfx/gui/image.h>
#include <niu2x/gfx/resource_manager.h>

namespace niu2x::gfx::gui {
Image::Image() { set_measure(); }
Image::~Image() { }

void Image::update_canvas()
{
    auto c = canvas();

    c->clear();

    auto r = compute_self_rect();
    if (r.size.area() <= 0)
        return;

    if (image_) {

        c->add_image(*image_, r, false);
    }
}

void Image::set_image(const ResId& sheet, const String& name)
{
    image_ = ResourceManager::get()->get_image_sheet_frame(sheet, name);
}

math::Size<float> Image::measure(const SizeRange& size_range)
{
    unused(size_range);
    return image_->region().size;
}

void Image::set_image(ImageSheet::Frame* frame) { image_ = frame; }

} // namespace niu2x::gfx::gui