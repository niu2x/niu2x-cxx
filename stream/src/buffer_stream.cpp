#include <niu2x/stream/buffer_stream.h>

namespace niu2x::stream {

BufferReadStream::BufferReadStream(const Buffer& buffer)
: buffer_(buffer)
, read_pos_(0)
{
}

BufferReadStream::BufferReadStream(Buffer&& buffer)
: buffer_(std::move(buffer))
, read_pos_(0)
{
}

BufferReadStream::~BufferReadStream() { }

size_t BufferReadStream::read(uint8_t* buf, size_t size)
{
    auto buf_size = buffer_.size();
    if (read_pos_ >= buf_size)
        return 0;

    auto avaliable_size = buf_size - read_pos_;
    size = min(avaliable_size, size);

    buffer_.read(buf, read_pos_, size);
    read_pos_ += size;

    return size;
}

bool BufferReadStream::eof()
{
    auto buf_size = buffer_.size();
    return read_pos_ >= buf_size;
}

BufferWriteStream::BufferWriteStream()
: write_pos_(0)
{
}

BufferWriteStream::~BufferWriteStream() { }

void BufferWriteStream::write(const uint8_t* buf, size_t size)
{
    auto buf_size = buffer_.size();
    auto new_tail = write_pos_ + size;
    if (new_tail > buf_size) {
        buffer_.resize(new_tail);
    }

    buffer_.write(buf, write_pos_, size);

    write_pos_ += size;
}

} // namespace niu2x::stream