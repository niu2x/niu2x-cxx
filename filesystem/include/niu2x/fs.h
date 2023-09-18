#ifndef NIU2X_FS_H
#define NIU2X_FS_H

#include <niu2x/type.h>
#include <niu2x/fs/path.h>
#include <niu2x/fs/file_type.h>
#include <niu2x/fs/file.h>

namespace niu2x::fs {

NXAPI FileType file_type(const Path& path);
NXAPI bool exist(const Path& path);

} // namespace niu2x::fs

#endif