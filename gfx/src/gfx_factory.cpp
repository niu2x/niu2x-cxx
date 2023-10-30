#include <niu2x/gfx/gfx_factory.h>
#include "gl_vertex_buffer.h"
#include "rpsc_gl.h"

namespace niu2x::gfx {

namespace src = niu2x::gfx::rpsc::gl;

UniquePtr<VertexBuffer> GFX_Factory::create_vertex_buffer()
{
    return make_unique<GL_VertexBuffer>();
}

UniquePtr<RenderProgram> GFX_Factory::create_render_program(RenderProgramID id)
{

    RenderProgram::Options options;
    switch (id) {
        case RenderProgramID::COLOR: {
            options.source_code[RenderProgram::Stage::VERTEX]
                = src::color_vertex;
            options.source_code[RenderProgram::Stage::FRAGMENT]
                = src::color_fragment;
            break;
        }
    }
    return make_unique<GL_RenderProgram>(options);
}

} // namespace niu2x::gfx
