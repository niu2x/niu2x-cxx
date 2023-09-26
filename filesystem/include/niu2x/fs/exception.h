#ifndef NIU2X_FS_EXCEPTION_H
#define NIU2X_FS_EXCEPTION_H

#include <niu2x/type.h>
#include <niu2x/fs/path.h>

namespace niu2x::exception {

class FileAlreadyExists : public RuntimeError {
public:
    explicit FileAlreadyExists(const fs::Path& filename)
    : RuntimeError("File already exists: " + filename.string())
    {
    }
};

} // namespace niu2x::exception

#endif
