#include <nxc/archive_factory.h>
#include "archive_zip.h"

namespace nxc {

ArchiveFactory::ArchiveFactory() { }
ArchiveFactory::~ArchiveFactory() { }

Result<ArchivePtr> ArchiveFactory::create(const String& pathname)
{
    return static_cast<ArchivePtr>(NXC_MAKE_PTR(ArchiveZip, pathname));
}

Result<ArchivePtr> ArchiveFactory::create(const Data* data)
{
    return static_cast<ArchivePtr>(NXC_MAKE_PTR(ArchiveZip, data));
}

} // namespace nxc