#include <niu2x/fs/path.h>

namespace std_fs = std::filesystem;

namespace niu2x::fs {

AbsPath::AbsPath() { }

AbsPath::AbsPath(const char* path)
: path_(path)
{
    path_ = std_fs::absolute(path_);
}
AbsPath::AbsPath(const String& path)
: path_(path)
{
    path_ = std_fs::absolute(path_);
}

} // namespace niu2x::fs