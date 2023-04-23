#ifndef NXC_STREAM_H
#define NXC_STREAM_H

#include <nxc/api.h>
#include <nxc/utils.h>
#include <nxc/result.h>

namespace nxc {

class NXC_API ReadStream : private Noncopyable {
public:
    ReadStream();
    virtual ~ReadStream() = 0;

    Result<char> read_char();
    Result<void> readx(void* buf, size_t n);
    Result<size_t> read(void* buf, size_t n);

protected:
    virtual Result<size_t> _read(void* buf, size_t n) = 0;
};

class NXC_API WriteStream : private Noncopyable {
public:
    WriteStream();
    virtual ~WriteStream();

    Result<void> writex(const void* buf, size_t n);
    Result<size_t> write(const void* buf, size_t n);

protected:
    virtual Result<size_t> _write(const void* buf, size_t n) = 0;
};

class NXC_API Stream : public WriteStream, public ReadStream {
public:
    Stream() { }
    virtual ~Stream() { }

protected:
    virtual Result<size_t> _write(const void* buf, size_t n) = 0;
    virtual Result<size_t> _read(void* buf, size_t n) = 0;
};

using ReadStreamPtr = Ptr<ReadStream>;
using WriteStreamPtr = Ptr<WriteStream>;
using StreamPtr = Ptr<Stream>;

NXC_API extern WriteStream* const stdout;

} // namespace nxc

#endif