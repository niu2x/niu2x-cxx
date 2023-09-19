#ifndef NIU2X_FS_H
#define NIU2X_FS_H

#include <niu2x/type.h>
#include <niu2x/fs/path.h>
#include <niu2x/fs/file_type.h>
#include <niu2x/fs/file.h>
#include <niu2x/fs/exception.h>

namespace niu2x::fs {

NXAPI FileType file_type(const Path& path);
NXAPI bool exists(const Path& path);
NXAPI bool is_directory(const Path& path);
NXAPI void touch(const Path& path);
NXAPI void create_dir(const Path& path);
NXAPI void ensure_dirs(const Path& path);
} // namespace niu2x::fs

#endif