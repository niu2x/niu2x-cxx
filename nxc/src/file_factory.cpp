#include <nxc/file_factory.h>
#include "raw_memory_file.h"
#include "plain_file.h"

namespace nxc {

FilePtr FileFactory::create(const String& pathname)
{
    return PlainFile::create(pathname);
}

FilePtr FileFactory::create(RawMemoryPtr memory)
{
    return RawMemoryFile::create(memory);
}

FilePtr FileFactory::create(ConstRawMemoryPtr memory)
{
    return RawMemoryFile::create(memory);
}

FileFactory* FileFactory::get()
{
    static FileFactory instance;
    return &instance;
}

} // namespace nxc