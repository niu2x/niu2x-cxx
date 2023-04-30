#include <nxc/archive_factory.h>
#include "archive_zip.h"

namespace nxc {

ArchiveFactory::ArchiveFactory() { }
ArchiveFactory::~ArchiveFactory() { }

ArchivePtr ArchiveFactory::create(const String& pathname)
{
    return NXC_MAKE_PTR(ArchiveZip, pathname);
}

} // namespace nxc