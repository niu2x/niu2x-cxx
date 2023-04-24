#ifndef NXC_ARCHIVE_H
#define NXC_ARCHIVE_H

#include <nxc/api.h>
#include <nxc/utils.h>
#include <nxc/file.h>

namespace nxc {

class NXC_API Archive : private Noncopyable {
public:
    Archive();
    virtual ~Archive() = 0;

    NXC_INLINE Result<void> open(OpenMode mode = OpenMode::READ)
    {
        return _open(mode);
    }

    NXC_INLINE void close() { _close(); }

    NXC_INLINE FilePtr open_entry(const String& entry)
    {
        return _open_entry(entry);
    }

    NXC_INLINE void close_entry(FilePtr file) { _close_entry(file); }

    NXC_INLINE bool exist_entry(const String& entry) const
    {
        return _exist_entry(entry);
    }

protected:
    virtual Result<void> _open(OpenMode mode) = 0;
    virtual void _close() = 0;

    virtual FilePtr _open_entry(const String& entry) = 0;
    virtual void _close_entry(FilePtr file) = 0;
    virtual bool _exist_entry(const String& entry) const = 0;
};

using ArchivePtr = Ptr<Archive>;

} // namespace nxc

#endif