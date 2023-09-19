#include <niu2x/fs/path.h>

namespace niu2x::fs {

Path::Path() { }

Path::Path(const String& path)
: BasePath(path)
{
}

Path::~Path() { }

} // namespace niu2x::fs