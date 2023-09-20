#ifndef NIU2X_STREAM_BASE_STREAM_H
#define NIU2X_STREAM_BASE_STREAM_H

#include <niu2x/type.h>
#include <niu2x/noncopyable.h>

namespace niu2x::stream {

class NXAPI BaseReadStream : private Noncopyable {
public:
    BaseReadStream();
    virtual ~BaseReadStream();
    virtual size_t read(void* buf, size_t size) = 0;
    virtual bool eof() = 0;
};

class NXAPI BaseWriteStream : private Noncopyable {
public:
    BaseWriteStream();
    virtual ~BaseWriteStream();
    virtual void write(const void* buf, size_t size) = 0;
    virtual void flush() { }
};

} // namespace niu2x::stream

#endif