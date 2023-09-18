#include <niu2x/fs.h>

namespace niu2x::fs {

File::File(const Path& path)
: path_(path)
{
}
File::~File() { }

bool File::exist() { return fs::exist(path_); }

} // namespace niu2x::fs