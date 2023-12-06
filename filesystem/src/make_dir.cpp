#include <niu2x/fs.h>

namespace std_fs = std::filesystem;

namespace niu2x::fs {

void create_dir(const Path& path)
{
    if (!std_fs::create_directory(path.native())) {
        throw FileAlreadyExists(path);
    }
}

void ensure_dirs(const Path& path)
{
    std_fs::create_directories(path.native());
}

} // namespace niu2x::fs