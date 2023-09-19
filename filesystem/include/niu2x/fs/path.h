#ifndef NIU2X_FS_PATH_H
#define NIU2X_FS_PATH_H

#include <filesystem>
#include <niu2x/type.h>

namespace niu2x::fs {

using BasePath = std::filesystem::path;

class NXAPI Path : public BasePath {
public:
    explicit Path(const String&);
    Path();
    ~Path();
};

}; // namespace niu2x::fs

#endif