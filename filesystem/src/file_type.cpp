#include <niu2x/fs.h>
#include "build_time/build_config.h"
#include <filesystem>

// #if NIU2X_USE_POSIX
//     #include <sys/types.h>
//     #include <sys/stat.h>
//     #include <unistd.h>
// #endif

namespace niu2x::fs {

FileType file_type(const Path& path)
{
    auto f_status = std::filesystem::status(path);
    auto f_type = f_status.type();

    FileType ft = FileType::NONE;
    using std_ftype = std::filesystem::file_type;

    switch (f_type) {
        case std_ftype::none:
        case std_ftype::not_found: {
            throw_os_err();
            break;
        }
        case std_ftype::socket:{   
            ft = FileType::SOCKET;
            break;
        }
        case std_ftype::symlink:{   
            ft = FileType::SYMBOLIC_LINK;
            break;
        }

        case std_ftype::regular:{   
            ft = FileType::REGULAR_FILE;
            break;
        }
        case std_ftype::block:{   
            ft = FileType::BLOCK_DEVICE;
            break;
        }
        case std_ftype::directory:{   
            ft = FileType::DIRECTORY;
            break;
        }
        case std_ftype::character:{   
            ft = FileType::CHARACTER_DEVICE;
            break;
        }
        case std_ftype::fifo:{   
            ft = FileType::FIFO;
            break;
        }
    }
    return ft;

}

} // namespace niu2x::fs