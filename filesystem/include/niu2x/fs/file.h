#ifndef NIU2X_FS_FILE_H
#define NIU2X_FS_FILE_H

#include <niu2x/noncopyable.h>
#include <niu2x/type.h>
#include <niu2x/fs/path.h>

namespace niu2x::fs {

class File : private Noncopyable {
public:
    File(const Path& path);
    ~File();
    bool exist();

private:
    Path path_;
};

} // namespace niu2x::fs

#endif