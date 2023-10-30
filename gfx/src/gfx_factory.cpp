#include <niu2x/gfx/gfx_factory.h>
#include "gl_vertex_buffer.h"

namespace niu2x::gfx {

UniquePtr<VertexBuffer> GFX_Factory::create_vertex_buffer()
{
    return make_unique<GL_VertexBuffer>();
}

} // namespace niu2x::gfx
