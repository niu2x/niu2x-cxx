#ifndef NXC_BUFFER_STREAM_H
#define NXC_BUFFER_STREAM_H

#include <nxc/utils.h>
#include <nxc/stream.h>
#include <nxc/buffer.h>

namespace nxc {

class BufferWriteStream : public WriteStream {
public:
    BufferWriteStream(Buffer* buffer);
    virtual ~BufferWriteStream();

protected:
    virtual Result<size_t> _write(const void* buf, size_t n) override;

private:
    Buffer* buffer_;
};

class BufferReadStream : public ReadStream {
public:
    BufferReadStream(const Buffer* buffer);
    virtual ~BufferReadStream();

protected:
    virtual Result<size_t> _read(void* buf, size_t n) override;

private:
    const Buffer* buffer_;
    size_t pos_;
};

} // namespace nxc

#endif