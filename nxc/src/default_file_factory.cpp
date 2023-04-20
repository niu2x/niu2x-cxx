#include <nxc/default_file_factory.h>
#include "raw_memory_file.h"
#include "plain_file.h"

namespace nxc {

FilePtr DefaultFileFactory::create(const String& pathname)
{
    return PlainFile::create(pathname);
}

FilePtr DefaultFileFactory::create(RawMemoryPtr memory)
{
    return RawMemoryFile::create(memory);
}

FilePtr DefaultFileFactory::create(ConstRawMemoryPtr memory)
{
    return RawMemoryFile::create(memory);
}

} // namespace nxc