#ifndef NXC_ARCHIVE_FACTORY_H
#define NXC_ARCHIVE_FACTORY_H

#include <nxc/api.h>
#include <nxc/utils.h>
#include <nxc/archive.h>

namespace nxc {

class NXC_API ArchiveFactory : public Singleton<ArchiveFactory> {
public:
    ArchiveFactory();
    ~ArchiveFactory();
    ArchivePtr create(const String& pathname);
};

} // namespace nxc

#endif