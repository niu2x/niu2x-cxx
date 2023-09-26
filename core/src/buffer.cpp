#include <niu2x/type.h>

namespace niu2x {

Buffer::Buffer(size_t capacity)
: buf_(make_shared<MemBlock>())

{
    buf_->resize(capacity);
}

Buffer::~Buffer() { }

void Buffer::write(const void* data, size_t offset, size_t size)
{
    assert(size + offset <= buf_->size());
    memcpy(buf_->data() + offset, data, size);
}

void Buffer::read(void* data, size_t offset, size_t size) const
{
    assert(buf_->size() - offset >= size);
    memcpy(data, buf_->data() + offset, size);
}

} // namespace niu2x