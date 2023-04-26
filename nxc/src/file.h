#ifndef NXC_FILE_INTERFACE_H
#define NXC_FILE_INTERFACE_H

#include <nxc/api.h>
#include <nxc/utils.h>
#include <nxc/result.h>
#include <nxc/stream.h>

namespace nxc {

class File : private Noncopyable {
public:
    enum class SeekPos {
        BEGIN,
        CURR,
        END,
    };

    File();
    virtual ~File() = 0;

    NXC_INLINE Result<void> open(OpenMode mode = OpenMode::READ)
    {
        return _open(mode);
    }

    NXC_INLINE void close() { _close(); }

    NXC_INLINE Result<void> rewind() { return seek(SeekPos::BEGIN, 0); }

    NXC_INLINE Result<size_t> read(void* buf, size_t n)
    {
        return _read(buf, n);
    }

    NXC_INLINE Result<size_t> write(const void* buf, size_t n)
    {
        return _write(buf, n);
    }

    NXC_INLINE Result<void> seek(SeekPos relative, long offset)
    {
        return _seek(relative, offset);
    }
    NXC_INLINE Result<long> tell() const { return _tell(); }

protected:
    virtual Result<void> _seek(SeekPos relative, long offset) = 0;
    virtual Result<long> _tell() const = 0;
    virtual Result<size_t> _read(void* buf, size_t n) = 0;
    virtual Result<size_t> _write(const void* buf, size_t n) = 0;
    virtual Result<void> _open(OpenMode mode) = 0;
    virtual void _close() = 0;
};

using FilePtr = Ptr<File>;
using ConstFilePtr = Ptr<const File>;

} // namespace nxc
#endif