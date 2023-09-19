#include <niu2x/fs.h>
#include <filesystem>

namespace niu2x::fs {

void remove(const Path& path)
{
    if (exists(path)) {
        if (std::filesystem::remove_all(path) <= 0) {
            throw_runtime_err(
                "std::filesystem::remove_all for " + path.string());
        }
    }
}

} // namespace niu2x::fs
