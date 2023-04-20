#ifndef NXC_DEFAULT_ARCHIVE_FACTORY_H
#define NXC_DEFAULT_ARCHIVE_FACTORY_H

#include <nxc/archive_factory.h>

namespace nxc {

class NXC_API DefaultArchiveFactory : public ArchiveFactory {
public:
    DefaultArchiveFactory() { }
    virtual ~DefaultArchiveFactory() { }
    virtual ArchivePtr create(const String& pathname) override;
};

} // namespace nxc

#endif