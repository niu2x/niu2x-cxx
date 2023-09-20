#include <niu2x/fs.h>
namespace niu2x::fs {

void touch(const Path& path)
{
    if (exists(path))
        return;

    FILE* fp = fopen(path.c_str(), "w");
    if (!fp)
        throw_os_err();

    fclose(fp);
}

} // namespace niu2x::fs