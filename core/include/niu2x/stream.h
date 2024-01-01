#ifndef NIU2X_SRREAM_H
#define NIU2X_SRREAM_H

#include <niu2x/noncopyable.h>
#include <niu2x/convention.h>
#include <niu2x/std_alias.h>

namespace niu2x {

class ReadStream : private Noncopyable {
public:
    virtual ~ReadStream();
    virtual NR read(void* buf, NR size) = 0;
    virtual bool eof() = 0;
};

class WriteStream : private Noncopyable {
public:
    virtual ~WriteStream();
    virtual void write(const void* buf, NR size) = 0;
    virtual void finalize() { }
};

void pipe(ReadStream* reader, WriteStream* writer, bool auto_finalize = true);

} // namespace niu2x

#endif