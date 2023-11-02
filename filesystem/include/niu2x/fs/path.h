#ifndef NIU2X_FS_PATH_H
#define NIU2X_FS_PATH_H

#include <filesystem>
#include <niu2x/type.h>
#include <niu2x/preprocess/class_utils.h>

namespace niu2x::fs {

using BasePath = std::filesystem::path;

class NXAPI Path : public BasePath {
public:
    Path(BasePath&&);
    Path(const BasePath&);
    Path(const char*);
    Path(const String&);

    NIU2X_CLASS_DEFAULT_MOVABLE(Path);
    NIU2X_CLASS_DEFAULT_COPYABLE(Path);

    Path();
    ~Path();

    Path parent() const { return Path(parent_path()); }
    Path abs() const { return std::filesystem::absolute(*this); }
};

}; // namespace niu2x::fs

#endif