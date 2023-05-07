#ifndef NXC_ARCHIVE_FACTORY_H
#define NXC_ARCHIVE_FACTORY_H

#include <nxc/api.h>
#include <nxc/utils.h>
#include <nxc/archive.h>
#include <nxc/data.h>
#include <nxc/result.h>

namespace nxc {

class NXC_API ArchiveFactory : public Singleton<ArchiveFactory> {
public:
    ArchiveFactory();
    ~ArchiveFactory();

    Result<ArchivePtr> create(const String& pathname);
    Result<ArchivePtr> create(const Data* data);
};

} // namespace nxc

#endif