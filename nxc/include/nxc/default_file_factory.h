#ifndef NXC_DEFAULT_FILE_FACTORY_H
#define NXC_DEFAULT_FILE_FACTORY_H

#include <nxc/file_factory.h>

namespace nxc {

class NXC_API DefaultFileFactory : public FileFactory {
public:
    DefaultFileFactory() { }
    virtual ~DefaultFileFactory() { }

    virtual FilePtr create(const String& pathname) override;
    virtual FilePtr create(RawMemoryPtr memory) override;
    virtual FilePtr create(ConstRawMemoryPtr memory) override;
};

} // namespace nxc

#endif