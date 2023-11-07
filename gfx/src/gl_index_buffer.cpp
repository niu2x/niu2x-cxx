#include <niu2x/type/exception.h>
#include "gl_vertex_buffer.h"

namespace niu2x::gfx {

void GL_IndexBuffer::resize(NR count)
{
    if (max_index_count_ != count) {
        bind();
        auto bytes = sizeof(uint16_t) * count;
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, bytes, nullptr, GL_DYNAMIC_DRAW);
        max_index_count_ = count;
    }
}

void GL_IndexBuffer::set(NR offset, NR count, const uint16_t* data)
{
    if (offset + count > max_index_count_) {
        throw_runtime_err("too many vertex");
    }

    bind();
    auto offset_bytes = offset * sizeof(uint16_t);
    auto bytes = sizeof(uint16_t) * count;
    glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, offset_bytes, bytes, data);
}

NR GL_IndexBuffer::size() const { return max_index_count_; }

void GL_IndexBuffer::bind()
{
    if (current_binding_id_ != native_id_) {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, native_id_);
    }

    current_binding_id_ = native_id_;
}

GL_IndexBuffer::GL_IndexBuffer() { glGenBuffers(1, &native_id_); }

GL_IndexBuffer::~GL_IndexBuffer() { glDeleteBuffers(1, &native_id_); }

GLuint GL_IndexBuffer::current_binding_id_ = 0;

} // namespace niu2x::gfx