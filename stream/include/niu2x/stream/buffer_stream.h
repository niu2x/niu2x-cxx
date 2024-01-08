#ifndef NIU2X_STREAM_BUFFER_STREAM_H
#define NIU2X_STREAM_BUFFER_STREAM_H

#include <niu2x/base_stream.h>
#include <niu2x/preprocess.h>
#include <niu2x/buffer.h>

namespace niu2x::stream {

class BufferByteReadStream : public ByteReadStream {
public:
    BufferByteReadStream();
    BufferByteReadStream(BufferPtr buffer);
    virtual ~BufferByteReadStream();
    virtual size_t read(uint8_t* buf, size_t size) override;
    virtual bool eof() override;

    NIU2X_PP_MOVABLE(BufferByteReadStream);

private:
    BufferPtr buffer_;
    size_t read_pos_;
};

class BufferByteWriteStream : public ByteWriteStream {
public:
    BufferByteWriteStream();
    BufferByteWriteStream(BufferPtr buffer);
    virtual ~BufferByteWriteStream();
    virtual void write(const uint8_t* buf, size_t size) override;

    NIU2X_PP_MOVABLE(BufferByteWriteStream);

    const Buffer* buffer() const { return buffer_.get(); }

    Buffer* buffer() { return buffer_.get(); }

private:
    BufferPtr buffer_;
    size_t write_pos_;
};

} // namespace niu2x::stream

#endif
