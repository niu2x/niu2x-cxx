#ifndef NIU2X_STREAM_BUFFER_STREAM_H
#define NIU2X_STREAM_BUFFER_STREAM_H

#include <niu2x/type.h>

namespace niu2x::stream {

class NXAPI BufferReadStream : public ReadStream {
public:
    BufferReadStream(const Buffer& buffer);
    BufferReadStream(Buffer&& buffer);
    virtual ~BufferReadStream();
    virtual size_t read(void* buf, size_t size) override;
    virtual bool eof() override;

private:
    Buffer buffer_;
    size_t read_pos_;
};

class NXAPI BufferWriteStream : public WriteStream {
public:
    BufferWriteStream();
    virtual ~BufferWriteStream();
    virtual void write(const void* buf, size_t size) override;
    const Buffer& buffer() const { return buffer_; }
    Buffer&& move_buffer() { return std::move(buffer_); }

private:
    Buffer buffer_;
    size_t write_pos_;
};

} // namespace niu2x::stream

#endif
