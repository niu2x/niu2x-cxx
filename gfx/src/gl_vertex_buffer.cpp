#include "gl_vertex_buffer.h"

namespace niu2x::gfx {

GLuint GL_VertexBuffer::current_binding_id_ = 0;

GL_VertexBuffer::GL_VertexBuffer() { glGenBuffers(1, &native_id_); }

GL_VertexBuffer::~GL_VertexBuffer() { glDeleteBuffers(1, &native_id_); }

void GL_VertexBuffer::resize(NR vertex_count)
{
    bind();
    auto bytes = sizeof(Vertex) * vertex_count;
    glBufferData(GL_ARRAY_BUFFER, bytes, nullptr, GL_DYNAMIC_DRAW);
}

void GL_VertexBuffer::set_vertexs(NR offset, NR count, const Vertex* vertexs)
{
    bind();
    auto offset_bytes = offset * sizeof(Vertex);
    auto bytes = sizeof(Vertex) * count;
    glBufferSubData(GL_ARRAY_BUFFER, offset_bytes, bytes, vertexs);
}

#define OFFSET(n) ((void*)((n) * sizeof(float)))

void GL_VertexBuffer::bind()
{
    constexpr auto vertex_size = sizeof(Vertex);
    if (current_binding_id_ != native_id_) {
        glBindBuffer(GL_ARRAY_BUFFER, native_id_);
    }

    if (current_binding_id_ == 0) {

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, vertex_size, (void*)0);

        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, vertex_size, OFFSET(3));

        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, vertex_size, OFFSET(7));
    }

    current_binding_id_ = native_id_;
}

} // namespace niu2x::gfx