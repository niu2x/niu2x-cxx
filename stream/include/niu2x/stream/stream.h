#ifndef NIU2X_STREAM_BASE_STREAM_H
#define NIU2X_STREAM_BASE_STREAM_H

#include <niu2x/type.h>
#include <niu2x/noncopyable.h>

namespace niu2x::stream {

class NXAPI ReadStream : private Noncopyable {
public:
    ReadStream();
    virtual ~ReadStream();
    virtual size_t read(void* buf, size_t size) = 0;
    virtual bool eof() = 0;
};

class NXAPI WriteStream : private Noncopyable {
public:
    WriteStream();
    virtual ~WriteStream();
    virtual void write(const void* buf, size_t size) = 0;
    virtual void finalize() { }
};

} // namespace niu2x::stream

#endif