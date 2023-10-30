#ifndef NIU2X_GFX_GL_RENDER_PROGRAM_H
#define NIU2X_GFX_GL_RENDER_PROGRAM_H

#include <niu2x/gfx/hardward_resource.h>
#include "glad/glad.h"

namespace niu2x::gfx {

class GL_RenderProgram : public RenderProgram, private Noncopyable {
public:
    GL_RenderProgram(const RenderProgramOptions& options);
    ~GL_RenderProgram();

private:
    GLuint native_id_;
};

} // namespace niu2x::gfx

#endif