#ifndef NIU2X_FS_FILE_H
#define NIU2X_FS_FILE_H

#include <fstream>
#include <niu2x/noncopyable.h>
#include <niu2x/type/std_alias.h>
#include <niu2x/fs/path.h>
#include <niu2x/fs/open_mode.h>
#include <niu2x/preprocess/class_utils.h>

namespace niu2x::fs {

class NXAPI File : private Noncopyable {
public:
    explicit File(const Path& path);
    explicit File(Path&& path);

    bool exists() const;
    void touch() const;
    void create_dir() const;
    void ensure_dirs() const;
    void remove() const;
    File parent() const;
    const Path& path() const { return path_; }
    bool open(OpenMode open_mode);
    bool eof() const;

private:
    Path path_;
    UniquePtr<std::fstream> fs_;
};

static_assert(is_movable<File>);

} // namespace niu2x::fs

#endif