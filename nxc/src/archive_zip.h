#ifndef NXC_ARCHIVE_ZIP_H
#define NXC_ARCHIVE_ZIP_H

#include <nxc/archive.h>
#include "file.h"
#include <nxc/buffer.h>
#include <zip.h>

namespace nxc {

class ArchiveZip : public Archive {
public:
    using ReadStreamPtrVector = Vector<ReadStreamPtr>;
    ArchiveZip(const String& pathname);
    virtual ~ArchiveZip();

protected:
    virtual Result<void> _open(OpenMode mode) override;
    virtual void _close() override;

    virtual ReadStreamPtr _read_entry(const String& entry) override;
    virtual bool _exist_entry(const String& entry) const override;

private:
    String pathname_;
    OpenMode mode_;
    zip_t* zip_;
    int read_streams_;
};

} // namespace nxc

#endif