#ifndef NXC_BUFFER_STREAM_H
#define NXC_BUFFER_STREAM_H

#include <nxc/utils.h>
#include <nxc/stream.h>
#include <nxc/buffer.h>

namespace nxc {

class BufferWriteStream : public WriteStream {
public:
    BufferWriteStream(Buffer& buffer);
    virtual ~BufferWriteStream();

protected:
    virtual Result<size_t> _write(const void* buf, size_t n) override;

private:
    Buffer& buffer_;
};

} // namespace nxc

#endif