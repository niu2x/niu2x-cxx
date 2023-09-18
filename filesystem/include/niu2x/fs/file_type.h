#ifndef NIU2X_FS_FILE_TYPE_H
#define NIU2X_FS_FILE_TYPE_H

namespace niu2x::fs {

enum class FileType {
    NONE,
    SOCKET,
    SYMBOLIC_LINK,
    REGULAR_FILE,
    BLOCK_DEVICE,
    DIRECTORY,
    CHARACTER_DEVICE,
    FIFO,
};

}; // namespace niu2x::fs

#endif