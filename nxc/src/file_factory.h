#ifndef NXC_FILE_FACTORY_H
#define NXC_FILE_FACTORY_H

#include "file.h"

namespace nxc {

class FileFactory : public Singleton<FileFactory> {
public:
    FileFactory() { }
    ~FileFactory() { }

    FilePtr create(const String& pathname);
};

using FileFactoryPtr = Ptr<FileFactory>;

} // namespace nxc

#endif