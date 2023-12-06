#ifndef NIU2X_FS_PATH_H
#define NIU2X_FS_PATH_H

#include <filesystem>
#include <niu2x/type.h>
#include <niu2x/preprocess/class_utils.h>

namespace niu2x::fs {

using BasePath = std::filesystem::path;

class NXAPI AbsPath {
public:
    AbsPath();
    AbsPath(const char*);
    AbsPath(const String&);

    AbsPath parent() const { return AbsPath(path_.parent_path()); }

    String str() const { return path_.string(); }

    const BasePath& native() const { return path_; }

    String filename() const { return path_.filename(); }

private:
    BasePath path_ = "";
    bool valid_ = false;
};

static_assert(type_pred::is_movable<AbsPath>);
static_assert(type_pred::is_copyable<AbsPath>);

using Path = AbsPath;

}; // namespace niu2x::fs

#endif