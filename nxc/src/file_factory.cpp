#include "file_factory.h"
#include "plain_file.h"

namespace nxc {

FilePtr FileFactory::create(const String& pathname)
{
    return PlainFile::create(pathname);
}

} // namespace nxc