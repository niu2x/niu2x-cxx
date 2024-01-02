#ifndef NIU2X_STREAM_BUFFER_STREAM_H
#define NIU2X_STREAM_BUFFER_STREAM_H

#include <niu2x/base_stream.h>
#include <niu2x/buffer.h>

namespace niu2x::stream {

class BufferReadStream : public ByteReadStream {
public:
    BufferReadStream(const Buffer& buffer);
    BufferReadStream(Buffer&& buffer);
    virtual ~BufferReadStream();
    virtual size_t read(uint8_t* buf, size_t size) override;
    virtual bool eof() override;

private:
    Buffer buffer_;
    size_t read_pos_;
};

class BufferWriteStream : public ByteWriteStream {
public:
    BufferWriteStream();
    virtual ~BufferWriteStream();
    virtual void write(const uint8_t* buf, size_t size) override;
    const Buffer& buffer() const { return buffer_; }
    Buffer&& move_buffer() { return std::move(buffer_); }

private:
    Buffer buffer_;
    size_t write_pos_;
};

} // namespace niu2x::stream

#endif
