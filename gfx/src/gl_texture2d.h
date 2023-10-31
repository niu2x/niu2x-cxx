#ifndef NIU2X_GFX_GL_TEXTURE2D_H
#define NIU2X_GFX_GL_TEXTURE2D_H

#include <niu2x/gfx/hardward_resource.h>
#include "glad/glad.h"

namespace niu2x::gfx {

class GL_Texture2D : public Texture2D, private Noncopyable {
public:
    GL_Texture2D();
    ~GL_Texture2D();

    void resize(IntSize size, PixelFormat format) override;
    void bind(Index slot) override;
    void set_data(const IntRect& region, const void* pixel_data) override;

private:
    GLuint native_id_ = 0;

    GLenum internal_format_ = 0;
    GLenum format_ = 0;

    static GLuint current_binding_ids_[4];
};

} // namespace niu2x::gfx

#endif