#include <niu2x/fs.h>

namespace niu2x::fs {

bool is_directory(const Path& path)
{
    return exists(path) && file_type(path) == FileType::DIRECTORY;
}

} // namespace niu2x::fs