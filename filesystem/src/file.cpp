#include <niu2x/fs/file.h>
#include <niu2x/unused.h>
#include <niu2x/fs/simple_func.h>
#include <niu2x/fs/exception.h>

using si = std::ios_base;

namespace niu2x::fs {

File::File(const Path& path)
: path_(path)
{
}

File::File(Path&& path)
: path_(std::move(path))
{
}

bool File::exists() const { return fs::exists(path_); }

void File::touch() const { fs::touch(path_); }

void File::create_dir() const { fs::create_dir(path_); }

void File::ensure_dirs() const { fs::ensure_dirs(path_); }

void File::remove() const { fs::remove(path_); }

File File::parent() const { return File(path_.parent()); }

bool File::open(OpenMode open_mode)
{
    if (fs_) {
        throw FileAlreadyOpen(path_);
    }

    si::openmode mode = open_mode == OpenMode::READ ? si::in : si::out;

    fs_ = make_unique<std::fstream>();
    fs_->open(path_, mode);

    bool open_succ = fs_->is_open();
    if (!open_succ)
        fs_.reset();
    return open_succ;
}

} // namespace niu2x::fs