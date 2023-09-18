#include <niu2x/fs.h>

namespace niu2x::fs {

File::File(const Path& path)
: path_(path)
{
}
File::~File() { }

bool File::exists() { return fs::exists(path_); }

} // namespace niu2x::fs