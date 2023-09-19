#include <niu2x/fs.h>

namespace std_fs = std::filesystem;

namespace niu2x::fs {

void make_dir(const Path& path)
{
    if (!std_fs::create_directory(path)) {
        throw exception::FileAlreadyExists(path);
    }
}

void make_dirs(const Path& path) { std_fs::create_directories(path); }

} // namespace niu2x::fs