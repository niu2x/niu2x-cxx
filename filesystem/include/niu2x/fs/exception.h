#ifndef NIU2X_FS_EXCEPTION_H
#define NIU2X_FS_EXCEPTION_H

#include <niu2x/type.h>
#include <niu2x/fs/path.h>

namespace niu2x::fs {

class FileAlreadyExists : public RuntimeError {
public:
    explicit FileAlreadyExists(const fs::Path& filename)
    : RuntimeError("File already exists: " + filename.string())
    {
    }
};

class FileAlreadyOpen : public RuntimeError {
public:
    explicit FileAlreadyOpen(const fs::Path& filename)
    : RuntimeError("File already open: " + filename.string())
    {
    }
};

class FileNotExists : public RuntimeError {
public:
    explicit FileNotExists(const fs::Path& filename)
    : RuntimeError("File not exists: " + filename.string())
    {
    }
};

} // namespace niu2x::fs

#endif
