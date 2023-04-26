#ifndef NXC_RAW_MEMORY_FILE_H
#define NXC_RAW_MEMORY_FILE_H

#include <nxc/api.h>
#include "file.h"
#include <nxc/raw_memory.h>

namespace nxc {

class RawMemoryFile : public File {
public:
    static Ptr<RawMemoryFile> create(RawMemoryPtr memory);
    static Ptr<RawMemoryFile> create(ConstRawMemoryPtr memory);

    RawMemoryFile(RawMemoryPtr memory);
    RawMemoryFile(ConstRawMemoryPtr memory);

    virtual ~RawMemoryFile();

protected:
    // virtual bool _eof() const override;
    virtual Result<void> _seek(SeekPos relative, long offset) override;
    virtual Result<long> _tell() const override;

    virtual Result<size_t> _read(void* buf, size_t n) override;
    virtual Result<size_t> _write(const void* buf, size_t n) override;
    virtual Result<void> _open(OpenMode mode) override
    {
        mode_ = mode;
        return E::OK;
    }
    virtual void _close() override { }

private:
    RawMemoryPtr memory_;
    ConstRawMemoryPtr const_memory_;
    long pos_;
    OpenMode mode_;
};

using RawMemoryFilePtr = Ptr<RawMemoryFile>;

} // namespace nxc

#endif