#ifndef NXC_FILE_FACTORY_H
#define NXC_FILE_FACTORY_H

#include <nxc/file.h>
#include <nxc/raw_memory.h>

namespace nxc {

class NXC_API FileFactory {
public:
    FileFactory() { }
    virtual ~FileFactory() { }

    virtual FilePtr create(const String& pathname) = 0;
    virtual FilePtr create(RawMemoryPtr memory) = 0;
    virtual FilePtr create(ConstRawMemoryPtr memory) = 0;
};

using FileFactoryPtr = Ptr<FileFactory>;

} // namespace nxc

#endif