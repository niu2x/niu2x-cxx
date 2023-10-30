#ifndef NIU2X_GFX_GL_VERTEX_BUFFER_H
#define NIU2X_GFX_GL_VERTEX_BUFFER_H

#include <niu2x/gfx/vertex_buffer.h>
#include "glad/glad.h"

namespace niu2x::gfx {

class GL_VertexBuffer : public VertexBuffer, private Noncopyable {
public:
    GL_VertexBuffer();
    ~GL_VertexBuffer();

    void resize(NR vertex_count) override;
    void set_vertex(NR offset, NR count, const Vertex*) override;

private:
    GLuint native_id_;
};

} // namespace niu2x::gfx

#endif