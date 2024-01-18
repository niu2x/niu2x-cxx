#include <niu2x/stream/buffer_stream.h>

namespace niu2x::stream {

BufferByteReadStream::BufferByteReadStream(BufferPtr buffer)
: buffer_(buffer)
, read_pos_(0)
{
}

BufferByteReadStream::BufferByteReadStream()
: buffer_(nullptr)
, read_pos_(0)
{
}

BufferByteReadStream::~BufferByteReadStream() { }

size_t BufferByteReadStream::read(uint8_t* buf, size_t size)
{
    auto buf_size = buffer_->size();
    if (read_pos_ >= buf_size)
        return 0;

    auto avaliable_size = buf_size - read_pos_;
    size = std::min(avaliable_size, size);

    buffer_->read(buf, read_pos_, size);
    read_pos_ += size;

    return size;
}

bool BufferByteReadStream::eof()
{
    auto buf_size = buffer_->size();
    return read_pos_ >= buf_size;
}

BufferByteWriteStream::BufferByteWriteStream()
: buffer_(nullptr)
, write_pos_(0)
{
}

BufferByteWriteStream::BufferByteWriteStream(BufferPtr buffer)
: buffer_(buffer)
, write_pos_(0)
{
}

BufferByteWriteStream::~BufferByteWriteStream() { }

void BufferByteWriteStream::write(const uint8_t* buf, size_t size)
{
    auto buf_size = buffer_->size();
    auto new_tail = write_pos_ + size;
    if (new_tail > buf_size) {
        buffer_->resize(new_tail);
    }

    buffer_->write(buf, write_pos_, size);

    write_pos_ += size;
}

} // namespace niu2x::stream