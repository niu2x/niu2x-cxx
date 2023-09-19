#include <niu2x/fs.h>

namespace niu2x::fs {

File::File(const Path& path)
: path_(path)
{
}
File::~File() { }

bool File::exists() { return fs::exists(path_); }

void File::touch() { fs::touch(path_); }

void File::create_dir() { fs::create_dir(path_); }

void File::ensure_dirs() { fs::ensure_dirs(path_); }

void File::remove() { fs::remove(path_); }

} // namespace niu2x::fs