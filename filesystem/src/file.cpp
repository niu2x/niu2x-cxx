#include <niu2x/fs.h>

namespace niu2x::fs {

File::File(const Path& path)
: path_(path)
{
}

File::File(Path&& path)
: path_(std::move(path))
{
}

File::~File() { }

bool File::exists() const { return fs::exists(path_); }

void File::touch() const { fs::touch(path_); }

void File::create_dir() const { fs::create_dir(path_); }

void File::ensure_dirs() const { fs::ensure_dirs(path_); }

void File::remove() const { fs::remove(path_); }

File File::parent() const { return File(path_.parent()); }

} // namespace niu2x::fs