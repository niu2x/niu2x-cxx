#ifndef NXC_ARCHIVE_H
#define NXC_ARCHIVE_H

#include <nxc/api.h>
#include <nxc/utils.h>
#include <nxc/result.h>
#include <nxc/stream.h>

namespace nxc {

// reference
class NXC_API Archive : private Noncopyable {
public:
    Archive();
    virtual ~Archive() = 0;

    NXC_INLINE Result<void> open(OpenMode mode = OpenMode::READ)
    {
        return _open(mode);
    }

    NXC_INLINE void close() { _close(); }

    NXC_INLINE ReadStreamPtr read_entry(const String& entry)
    {
        return _read_entry(entry);
    }

    NXC_INLINE bool exist_entry(const String& entry) const
    {
        return _exist_entry(entry);
    }

protected:
    virtual Result<void> _open(OpenMode mode) = 0;
    virtual void _close() = 0;

    virtual ReadStreamPtr _read_entry(const String& entry) = 0;
    virtual bool _exist_entry(const String& entry) const = 0;
};

using ArchivePtr = Ptr<Archive>;

} // namespace nxc

#endif