#ifndef NIU2X_BASE_STREAM_H
#define NIU2X_BASE_STREAM_H

#include <niu2x/noncopyable.h>
#include <niu2x/convention.h>
#include <niu2x/exception.h>
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

    void write(const void* ptr, NR size)
    {
        write(reinterpret_cast<const T*>(ptr), size);
    }
    virtual void finalize() { }

    NIU2X_PP_MOVABLE(WriteStream);
};

class ByteReadStream : public ReadStream<uint8_t> {
public:
    ByteReadStream() { }
    ~ByteReadStream() { }

    void read_char(char* buf, NR size);

    template <class T>
    T read_value()
    {
        T n;
        if (read(&n, sizeof(T)) != sizeof(T)) {
            throw_runtime_err("no more bytes");
        }
        return n;
    }

    uint32_t read_u32() { return read_value<uint32_t>(); }
    uint16_t read_u16() { return read_value<uint16_t>(); }
    uint8_t read_u8() { return read_value<uint8_t>(); }
};

class ByteWriteStream : public WriteStream<uint8_t> {
public:
    ByteWriteStream() { }
    ~ByteWriteStream() { }

    void write_char(const char* buf, NR size);

    template <class T>
    void write_value(T n)
    {
        write(&n, sizeof(T));
    }

    void write_u32(uint32_t n) { write_value<uint32_t>(n); }
    void write_u16(uint16_t n) { write_value<uint16_t>(n); }
    void write_u8(uint8_t n) { write_value<uint8_t>(n); }
};

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