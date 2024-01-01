#ifndef NIU2X_FS_SIMPLE_FUNC_H
#define NIU2X_FS_SIMPLE_FUNC_H

#include <niu2x/std_alias.h>
#include <niu2x/fs/path.h>
#include <niu2x/fs/file_type.h>

namespace niu2x::fs {

FileType file_type(const AbsPath& path);
bool exists(const AbsPath& path);
bool is_directory(const AbsPath& path);
void touch(const AbsPath& path);
void create_dir(const AbsPath& path);
void ensure_dirs(const AbsPath& path);
void remove(const AbsPath& path);

} // namespace niu2x::fs

#endif