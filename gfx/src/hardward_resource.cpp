#include <niu2x/gfx/hardward_resource.h>
#include <niu2x/image.h>

namespace niu2x::gfx {

RenderProgram::~RenderProgram() { }

Texture2D::~Texture2D() { }

void Texture2D::load(ReadStream* in, PixelFormat format)
{
    image::Image image;
    image.load_from(in);
    resize(image.size(), format);
}

} // namespace niu2x::gfx