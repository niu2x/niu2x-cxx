#include <niu2x/fs.h>
#include "build_time/build_config.h"

#if NIU2X_USE_POSIX
    #include <sys/types.h>
    #include <sys/stat.h>
    #include <unistd.h>
#endif

namespace niu2x::fs {

FileType file_type(const Path& path)
{
    struct stat sb;
    if (stat(path.c_str(), &sb)) {
        throw_os_err();
    }

    FileType ft;
    switch ((sb.st_mode & S_IFMT)) {
        case S_IFSOCK: {
            ft = FileType::SOCKET;
            break;
        }
        case S_IFLNK: {
            ft = FileType::SYMBOLIC_LINK;
            break;
        }
        case S_IFREG: {
            ft = FileType::REGULAR_FILE;
            break;
        }
        case S_IFBLK: {
            ft = FileType::BLOCK_DEVICE;
            break;
        }
        case S_IFDIR: {
            ft = FileType::DIRECTORY;
            break;
        }
        case S_IFCHR: {
            ft = FileType::CHARACTER_DEVICE;
            break;
        }
        case S_IFIFO: {
            ft = FileType::FIFO;
            break;
        }
    }
    return ft;
}

} // namespace niu2x::fs