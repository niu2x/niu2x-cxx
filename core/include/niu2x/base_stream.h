#ifndef NIU2X_BASE_STREAM_H
#define NIU2X_BASE_STREAM_H

#include <niu2x/noncopyable.h>
#include <niu2x/convention.h>
#include <niu2x/std_alias.h>

namespace niu2x {

template <class T>
class ReadStream : private Noncopyable {
public:
    ReadStream() { }
    virtual ~ReadStream() { }
    virtual NR read(T* buf, NR size) = 0;
    NR read(void* ptr, NR size)
    {
        return read(reinterpret_cast<T*>(ptr), size);
    }
    virtual bool eof() = 0;
    NIU2X_PP_MOVABLE(ReadStream);
};

template <class T>
class WriteStream : private Noncopyable {
public:
    WriteStream() { }
    virtual ~WriteStream() { }
    virtual void write(const T* buf, NR size) = 0;
    virtual void finalize() { }

    NIU2X_PP_MOVABLE(WriteStream);
};

class ByteReadStream : public ReadStream<uint8_t> {
public:
    ByteReadStream() { }
    ~ByteReadStream() { }

    uint32_t read_u32();
    uint8_t read_u8();
    void read_char(char* buf, NR size);
};

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