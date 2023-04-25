#ifndef NXC_FILE_FACTORY_H
#define NXC_FILE_FACTORY_H

#include "file.h"
#include <nxc/raw_memory.h>

namespace nxc {

class FileFactory : public Singleton<FileFactory> {
public:
    FileFactory() { }
    ~FileFactory() { }

    FilePtr create(const String& pathname);
    FilePtr create(RawMemoryPtr memory);
    FilePtr create(ConstRawMemoryPtr memory);
};

using FileFactoryPtr = Ptr<FileFactory>;

} // namespace nxc

#endif