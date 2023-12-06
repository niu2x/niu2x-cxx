#include <niu2x/fs.h>
#include <iostream>
#include <fstream>
#include <filesystem>

namespace std_fs = std::filesystem;

namespace niu2x::fs {

FileType file_type(const Path& path)
{
    auto f_status = std::filesystem::status(path.native());
    auto f_type = f_status.type();

    FileType ft = FileType::NONE;
    using std_ftype = std::filesystem::file_type;

    switch (f_type) {
        case std_ftype::unknown:
        case std_ftype::none:
        case std_ftype::not_found: {
            throw_os_err();
            break;
        }
        case std_ftype::socket: {
            ft = FileType::SOCKET;
            break;
        }
        case std_ftype::symlink: {
            ft = FileType::SYMBOLIC_LINK;
            break;
        }

        case std_ftype::regular: {
            ft = FileType::REGULAR_FILE;
            break;
        }
        case std_ftype::block: {
            ft = FileType::BLOCK_DEVICE;
            break;
        }
        case std_ftype::directory: {
            ft = FileType::DIRECTORY;
            break;
        }
        case std_ftype::character: {
            ft = FileType::CHARACTER_DEVICE;
            break;
        }
        case std_ftype::fifo: {
            ft = FileType::FIFO;
            break;
        }
    }
    return ft;
}

bool is_directory(const Path& path)
{
    return exists(path) && file_type(path) == FileType::DIRECTORY;
}

bool exists(const Path& path) { return std::filesystem::exists(path.native()); }

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

void touch(const Path& path)
{
    if (exists(path))
        return;

    std::ofstream out_file(path.native());

    if (!out_file.is_open())
        throw_os_err();

    out_file.close();
}

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