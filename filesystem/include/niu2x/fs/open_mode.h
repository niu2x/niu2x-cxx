#ifndef NIU2X_FS_OPEN_MODE_H
#define NIU2X_FS_OPEN_MODE_H

namespace niu2x::fs {

enum class OpenMode {
    READ = 1,
    WRITE = 2,
    RW = 3,
};

}

#endif