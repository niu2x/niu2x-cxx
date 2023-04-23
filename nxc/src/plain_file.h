#ifndef NXC_PLAIN_FILE_H
#define NXC_PLAIN_FILE_H

#include <nxc/api.h>
#include <nxc/file.h>

namespace nxc {

class PlainFile : public File {
public:
    static Ptr<PlainFile> create(const String& path);

    PlainFile(const String& path);
    virtual ~PlainFile();

protected:
    virtual void _seek(int relative, size_t offset) override;
    virtual size_t _tell() const override;
    virtual bool _readable() const override;
    virtual bool _writable() const override;

    virtual Result<size_t> _read(void* buf, size_t n) override;
    virtual Result<size_t> _write(const void* buf, size_t n) override;

    virtual Result<void> _open(OpenMode mode) override;
    virtual void _close() override;

private:
    FILE* fp_;
    OpenMode mode_;
    String pathname_;
};

} // namespace nxc

#endif