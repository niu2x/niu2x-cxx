#include "gl_texture2d.h"

namespace niu2x::gfx {

GLuint GL_Texture2D::current_binding_ids_[4] = { 0, 0, 0, 0 };

GL_Texture2D::GL_Texture2D() { glGenTextures(1, &native_id_); }
GL_Texture2D::~GL_Texture2D() { glDeleteTextures(1, &native_id_); }

void GL_Texture2D::bind(Index slot)
{
    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_2D, native_id_);
    current_binding_ids_[slot] = native_id_;
}

void GL_Texture2D::resize(IntSize size, PixelFormat format)
{
    size_ = size;

    bind(3);

    switch (format) {
        case PixelFormat::RGBA_8888: {
            internal_format_ = GL_RGBA;
            format_ = GL_RGBA;
            break;
        }
        case PixelFormat::RGB_888: {
            internal_format_ = GL_RGB;
            format_ = GL_RGB;
            break;
        }
        case PixelFormat::R8: {
            internal_format_ = GL_RED;
            format_ = GL_RED;
            break;
        }
    }
    glTexImage2D(GL_TEXTURE_2D, 0, internal_format_, size.width, size.height, 0,
        format_, GL_UNSIGNED_BYTE, nullptr);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

void GL_Texture2D::set_data(const IntRect& region, const void* pixel_data)
{
    bind(3);
    glTexSubImage2D(GL_TEXTURE_2D, 0, region.origin.x, region.origin.y,
        region.size.width, region.size.height, format_, GL_UNSIGNED_BYTE,
        pixel_data);
}

} // namespace niu2x::gfx