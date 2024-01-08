#ifndef NIU2X_FS_PATH_H
#define NIU2X_FS_PATH_H

#include <filesystem>
#include <niu2x/preprocess.h>
#include <niu2x/logger.h>
#include <niu2x/std_alias.h>

namespace niu2x::fs {

class AbsPath {
public:
    using BasePath = std::filesystem::path;

    AbsPath();
    AbsPath(const char*);
    AbsPath(const String&);

    AbsPath parent() const { return AbsPath(path_.parent_path()); }

    String str() const { return path_.string(); }

    const BasePath& native() const { return path_; }

    String filename() const { return path_.filename(); }

    bool valid() const { return path_ != ""; }

    String ext() const;
    String extension() const { return ext(); }

private:
    BasePath path_ = "";
};

static_assert(type_pred::is_movable<AbsPath>);
static_assert(type_pred::is_copyable<AbsPath>);

inline Logger& operator<<(Logger& logger, const AbsPath& value)
{
    logger << value.str();
    return logger;
}

}; // namespace niu2x::fs

#endif