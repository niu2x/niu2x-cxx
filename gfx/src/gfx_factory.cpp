#include <niu2x/gfx/gfx_factory.h>
#include "gl_vertex_buffer.h"
#include "gl_texture2d.h"
#include "rpsc_gl.h"

namespace niu2x::gfx {

namespace src = niu2x::gfx::rpsc::gl;

UniquePtr<VertexBuffer> GFX_Factory::create_vertex_buffer()
{
    return make_unique<GL_VertexBuffer>();
}

UniquePtr<IndexBuffer> GFX_Factory::create_index_buffer()
{
    return make_unique<GL_IndexBuffer>();
}

UniquePtr<RenderProgram> GFX_Factory::create_render_program(RenderProgramID id)
{
    using Stage = RenderProgram::Stage;
    RenderProgram::Options options;
    switch (id) {
        case RenderProgramID::COLOR: {
            options.source_code[Stage::VERTEX] = src::color_vertex;
            options.source_code[Stage::FRAGMENT] = src::color_fragment;
            break;
        }

        case RenderProgramID::TEXTURE_COLOR: {
            options.source_code[Stage::VERTEX] = src::texture_color_vertex;
            options.source_code[Stage::FRAGMENT] = src::texture_color_fragment;
            break;
        }
        case RenderProgramID::TEXT: {
            options.source_code[Stage::VERTEX] = src::text_vertex;
            options.source_code[Stage::FRAGMENT] = src::text_fragment;
            break;
        }
    }
    return make_unique<GL_RenderProgram>(options);
}

UniquePtr<Texture2D> GFX_Factory::create_texture2d()
{
    return make_unique<GL_Texture2D>();
}

} // namespace niu2x::gfx
