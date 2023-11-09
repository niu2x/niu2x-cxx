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

void RenderProgram::set_uniforms(const UniformPacket& uniforms_)
{
    for (auto& elem : uniforms_) {
        switch (elem.first) {
            case Uniform::UNKNOWN: {
                break;
            }
            case Uniform::TEX_0: {
                set_uniform_integer(elem.first, get<int>(elem.second));
                break;
            }
            case Uniform::MODEL:
            case Uniform::VIEW:
            case Uniform::PROJECTION: {
                set_uniform_mat4(elem.first, get<Mat4>(elem.second));
                break;
            }
            case Uniform::MASK_COLOR: {
                set_uniform_4f(
                    elem.first,
                    reinterpret_cast<const float*>(&get<Color>(elem.second)));
                break;
            }
        }
    }
}

} // namespace niu2x::gfx