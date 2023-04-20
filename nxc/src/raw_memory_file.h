#ifndef NXC_RAW_MEMORY_FILE_H
#define NXC_RAW_MEMORY_FILE_H

#include <nxc/api.h>
#include <nxc/file.h>
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
    virtual void _seek(int relative, size_t offset) override;
    virtual size_t _tell() const override;
    virtual bool _readable() const override;
    virtual bool _writable() const override;

    virtual Result<size_t> _read(void* buf, size_t n) override;
    virtual Result<size_t> _write(const void* buf, size_t n) override;
    virtual Result<void> _open(int mode) override
    {
        mode_ = mode;
        return E::OK;
    }
    virtual void _close() override { }

private:
    RawMemoryPtr memory_;
    ConstRawMemoryPtr const_memory_;
    size_t pos_;
    int mode_;
};

using RawMemoryFilePtr = Ptr<RawMemoryFile>;

} // namespace nxc

#endif