#include <niu2x/gfx/hardward_resource.h>
#include <niu2x/image.h>

namespace niu2x::gfx {

RenderProgram::~RenderProgram() { }

Texture2D::~Texture2D() { }

void Texture2D::load(ReadStream* in, PixelFormat format)
{
    image::ImageData image_data;
    image_data.load_from(in);

    int channels = image_data.channels();
    auto size = image_data.size();

    switch (format) {
        case PixelFormat::RGBA_8888: {
            if (channels != 4)
                throw_runtime_err("incorrect channels");
            break;
        }
        case PixelFormat::RGB_888: {
            if (channels != 3)
                throw_runtime_err("incorrect channels");
            break;
        }
        case PixelFormat::R8: {
            if (channels != 1)
                throw_runtime_err("incorrect channels");
            break;
        }
    }

    resize(image_data.size(), format);
    set_data({ 0, 0, size.width, size.height }, image_data.data());
}

} // namespace niu2x::gfx