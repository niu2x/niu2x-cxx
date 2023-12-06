#include <niu2x/fs.h>
#include <filesystem>

namespace std_fs = std::filesystem;

namespace niu2x::fs {

void remove(const Path& path)
{
    if (!exists(path)) {
        return;
    }

    if (std_fs::remove_all(path.native()) <= 0) {
        throw_runtime_err("std::filesystem::remove_all for " + path.str());
    }
}

} // namespace niu2x::fs
