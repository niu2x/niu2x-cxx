#include "gl_vertex_buffer.h"

namespace niu2x::gfx {

GL_VertexBuffer::GL_VertexBuffer() { glGenBuffers(1, &native_id_); }

GL_VertexBuffer::~GL_VertexBuffer() { glDeleteBuffers(1, &native_id_); }

void GL_VertexBuffer::resize(NR vertex_count)
{
    auto bytes = sizeof(Vertex) * vertex_count;
    glNamedBufferData(native_id_, bytes, nullptr, GL_DYNAMIC_DRAW);
}

void GL_VertexBuffer::set_vertex(NR offset, NR count, const Vertex* vertexs)
{
    auto offset_bytes = offset * sizeof(Vertex);
    auto bytes = sizeof(Vertex) * count;
    glNamedBufferSubData(native_id_, offset_bytes, bytes, vertexs);
}

} // namespace niu2x::gfx