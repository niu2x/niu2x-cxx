#ifndef NIU2X_FS_FILE_H
#define NIU2X_FS_FILE_H

#include <niu2x/noncopyable.h>
#include <niu2x/type.h>
#include <niu2x/fs/path.h>
#include <niu2x/preprocess/class_utils.h>

namespace niu2x::fs {

class NXAPI File {
public:
    explicit File(const Path& path);
    explicit File(Path&& path);
    ~File();

    NIU2X_CLASS_DEFAULT_COPYABLE(File);
    NIU2X_CLASS_DEFAULT_MOVABLE(File);

    bool exists() const;
    void touch() const;
    void create_dir() const;
    void ensure_dirs() const;
    void remove() const;
    File parent() const;

    const Path& path() const { return path_; }

private:
    const Path path_;
};

} // namespace niu2x::fs

#endif