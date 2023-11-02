#ifndef NIU2X_FS_SIMPLE_FUNC_H
#define NIU2X_FS_SIMPLE_FUNC_H

#include <niu2x/type.h>
#include <niu2x/fs/path.h>
#include <niu2x/fs/file_type.h>

namespace niu2x::fs {

NXAPI FileType file_type(const Path& path);
NXAPI bool exists(const Path& path);
NXAPI bool is_directory(const Path& path);
NXAPI void touch(const Path& path);
NXAPI void create_dir(const Path& path);
NXAPI void ensure_dirs(const Path& path);
NXAPI void remove(const Path& path);

NXAPI void abs_path(const Path& path);
NXAPI void dirname(const Path& path);

} // namespace niu2x::fs

#endif