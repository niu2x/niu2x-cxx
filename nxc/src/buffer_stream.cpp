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

} // namespace nxc