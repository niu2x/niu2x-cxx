#ifndef NXC_ARCHIVE_ZIP_H
#define NXC_ARCHIVE_ZIP_H

#include <nxc/archive.h>
#include <nxc/file.h>
#include <nxc/buffer.h>
#include <zip.h>

namespace nxc {

class ArchiveZip : public Archive {
public:
    using FilePtrVector = Vector<FilePtr>;
    using BufferPtrVector = Vector<BufferPtr>;

    ArchiveZip(const String& pathname);
    virtual ~ArchiveZip();

protected:
    virtual Result<void> _open(int mode) override;
    virtual void _close() override;

    virtual File* _open_entry(const String& entry) override;
    virtual void _close_entry(File* file) override;
    virtual bool _exist_entry(const String& entry) const override;

private:
    String pathname_;
    int mode_;
    zip_t* zip_;

    FilePtrVector opened_files_;
    BufferPtrVector write_buffers_;
};

} // namespace nxc

#endif