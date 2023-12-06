#ifndef NIU2X_FS_EXCEPTION_H
#define NIU2X_FS_EXCEPTION_H

#include <niu2x/type.h>
#include <niu2x/fs/path.h>

namespace niu2x::fs {

class FileAlreadyExists : public RuntimeError {
public:
    explicit FileAlreadyExists(const Path& path)
    : RuntimeError("File already exists: " + path.str())
    {
    }
};

class FileAlreadyOpen : public RuntimeError {
public:
    explicit FileAlreadyOpen(const Path& path)
    : RuntimeError("File already open: " + path.str())
    {
    }
};

class FileNotExists : public RuntimeError {
public:
    explicit FileNotExists(const Path& path)
    : RuntimeError("File not exists: " + path.str())
    {
    }
};

} // namespace niu2x::fs

#endif
