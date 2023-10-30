#ifndef NIU2X_TYPE_SRREAM_DATA_H
#define NIU2X_TYPE_SRREAM_DATA_H

#include <niu2x/noncopyable.h>
#include <niu2x/type/std_alias.h>

namespace niu2x::stream {

class DataIn : private Noncopyable {
public:
    virtual ~DataIn() { }
    virtual size_t read(void* buf, size_t size) = 0;
    virtual bool eof() = 0;
};

class DataOut : private Noncopyable {
public:
    virtual ~DataOut() { }
    virtual void write(const void* buf, size_t size) = 0;
};

} // namespace niu2x::stream

#endif