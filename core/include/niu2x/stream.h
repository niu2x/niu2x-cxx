#ifndef NIU2X_STREAM_H
#define NIU2X_STREAM_H

#include <niu2x/noncopyable.h>
#include <niu2x/convention.h>
#include <niu2x/std_alias.h>

namespace niu2x {

template <class T>
class ReadStream : private Noncopyable {
public:
    virtual ~ReadStream() { }
    virtual NR read(T* buf, NR size) = 0;
    virtual bool eof() = 0;

    NIU2X_PP_MOVABLE(ReadStream);
};

template <class T>
class WriteStream : private Noncopyable {
public:
    virtual ~WriteStream() { }
    virtual void write(const T* buf, NR size) = 0;
    virtual void finalize() { }

    NIU2X_PP_MOVABLE(WriteStream);
};

using ByteReadStream = ReadStream<uint8_t>;
using ByteWriteStream = WriteStream<uint8_t>;

template <class T>
void pipe(
    ReadStream<T>* reader,
    WriteStream<T>* writer,
    bool auto_finalize = true)
{
    constexpr int bs = 4096;
    T block[bs];
    while (!reader->eof()) {
        auto n = reader->read(block, bs);
        writer->write(block, n);
    }
    if (auto_finalize) {
        writer->finalize();
    }
}

} // namespace niu2x

#endif