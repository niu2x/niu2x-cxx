#include <niu2x/type.h>

namespace niu2x {

Buffer::Buffer(size_t capacity) { buf_.resize(capacity); }

Buffer::~Buffer() { }

void Buffer::write(const void* data, size_t offset, size_t size)
{
    if (size + offset > buf_.size())
        throw OutOfRange("");

    memcpy(buf_.data() + offset, data, size);
}

void Buffer::read(void* data, size_t offset, size_t size) const
{
    if (buf_.size() - offset < size)
        throw OutOfRange("");

    memcpy(data, buf_.data() + offset, size);
}

} // namespace niu2x