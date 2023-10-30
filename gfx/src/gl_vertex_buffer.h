#ifndef NIU2X_GFX_GL_VERTEX_BUFFER_H
#define NIU2X_GFX_GL_VERTEX_BUFFER_H

#include <niu2x/gfx/hardward_resource.h>
#include "glad/glad.h"

namespace niu2x::gfx {

class GL_VertexBuffer : public VertexBuffer, private Noncopyable {
public:
    GL_VertexBuffer();
    ~GL_VertexBuffer();

    void resize(NR vertex_count) override;
    void set_vertexs(NR offset, NR count, const Vertex*) override;
    void bind() override;

private:
    GLuint native_id_;
    static GLuint current_binding_id_;
};

} // namespace niu2x::gfx

#endif