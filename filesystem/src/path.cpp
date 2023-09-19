#include <niu2x/fs/path.h>

namespace niu2x::fs {

Path::Path() { }

Path::Path(BasePath&& path)
: BasePath(std::move(path))
{
}

Path::Path(const BasePath& path)
: BasePath(path)
{
}

Path::Path(const char* path)
: BasePath(path)
{
}

Path::~Path() { }

} // namespace niu2x::fs