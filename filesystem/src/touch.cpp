#include <niu2x/fs.h>
#include <iostream>
#include <fstream>

namespace niu2x::fs {

void touch(const Path& path)
{
    if (exists(path))
        return;

    std::ofstream out_file(path.native());

    if (!out_file.is_open())
        throw_os_err();

    out_file.close();
}

} // namespace niu2x::fs