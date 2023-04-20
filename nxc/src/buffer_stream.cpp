#include "buffer_stream.h"

namespace nxc {

BufferWriteStream::BufferWriteStream(Buffer* buffer)
: buffer_(buffer)
{
}

BufferWriteStream::~BufferWriteStream() { }

Result<size_t> BufferWriteStream::_write(const void* buf, size_t n)
{
    buffer_->write(buf, n);
    return n;
}

Result<size_t> BufferReadStream::_read(void* buf, size_t n)
{
    auto available = buffer_->size() - pos_;
    n = min(available, n);

    if (!n)
        return E::END_OF_FILE;

    memcpy(buf, buffer_->data() + pos_, n);
    pos_ += n;

    return n;
}

BufferReadStream::BufferReadStream(const Buffer* buffer)
: buffer_(buffer)
, pos_(0)
{
}

BufferReadStream::~BufferReadStream() { }

} // namespace nxc