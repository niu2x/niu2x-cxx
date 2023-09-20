#include <niu2x/type.h>

namespace niu2x {

Buffer::Buffer(size_t capacity)
: buf_(make_shared<MemBlock>())

{
    buf_->resize(capacity);
}

Buffer::~Buffer() { }

// bool Buffer::eof() const { return read_pos_ >= size_; }

void Buffer::write(const void* data, off_t offset, size_t size)
{
    assert(size + offset <= buf_->size());
    memcpy(buf_->data() + offset, data, size);
}

void Buffer::read(void* data, off_t offset, size_t size) const
{
    assert(offset >= 0);
    assert(buf_->size() - offset >= size);

    memcpy(data, buf_->data() + offset, size);
}

} // namespace niu2x