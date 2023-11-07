#ifndef NIU2X_GFX_GL_RENDER_PROGRAM_H
#define NIU2X_GFX_GL_RENDER_PROGRAM_H

#include <niu2x/gfx/hardward_resource.h>
#include "glad/glad.h"

namespace niu2x::gfx {

class GL_RenderProgram : public RenderProgram, private Noncopyable {
public:
    GL_RenderProgram(const Options& options);
    ~GL_RenderProgram();

    void bind() override;
    void set_uniform_integer(Uniform uniform, int n) override;
    void set_uniform_mat4(Uniform uniform, const Mat4& m) override;
    void set_uniform_4f(Uniform uniform, const float* array) override;

private:
    GLuint native_id_;
    static GLuint current_binding_id_;
    HashMap<Uniform, GLuint> uniform_locations_;
};

} // namespace niu2x::gfx

#endif