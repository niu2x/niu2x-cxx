#ifndef NXC_FILE_INTERFACE_H
#define NXC_FILE_INTERFACE_H

#include <nxc/api.h>
#include <nxc/utils.h>
#include <nxc/result.h>
#include <nxc/stream.h>

namespace nxc {

class NXC_API File : private Noncopyable {
public:
    enum {
        S_BEGIN,
        S_END,
        S_CURR,
    };

    File();
    virtual ~File() = 0;

    NXC_INLINE Result<void> open(int mode = O_READ) { return _open(mode); }

    NXC_INLINE void close() { _close(); }

    NXC_INLINE void rewind() { seek(S_BEGIN, 0); }

    NXC_INLINE Result<size_t> read(void* buf, size_t n)
    {
        NXC_ASSERT(readable(), "read a non-readable file");
        return _read(buf, n);
    }
    NXC_INLINE Result<size_t> write(const void* buf, size_t n)
    {
        NXC_ASSERT(writable(), "write a non-writable file");
        return _write(buf, n);
    }

    // NXC_INLINE bool eof() const { return _eof(); }
    NXC_INLINE void seek(int relative, size_t offset)
    {
        _seek(relative, offset);
    }
    NXC_INLINE size_t tell() const { return _tell(); }
    NXC_INLINE bool readable() const { return _readable(); }
    NXC_INLINE bool writable() const { return _writable(); }

protected:
    virtual void _seek(int relative, size_t offset) = 0;
    virtual size_t _tell() const = 0;
    virtual bool _readable() const = 0;
    virtual bool _writable() const = 0;
    virtual Result<size_t> _read(void* buf, size_t n) = 0;
    virtual Result<size_t> _write(const void* buf, size_t n) = 0;
    virtual Result<void> _open(int mode) = 0;
    virtual void _close() = 0;
};

using FilePtr = Ptr<File>;
using ConstFilePtr = Ptr<const File>;

} // namespace nxc
#endif