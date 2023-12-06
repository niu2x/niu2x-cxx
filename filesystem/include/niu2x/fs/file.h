#ifndef NIU2X_FS_FILE_H
#define NIU2X_FS_FILE_H

#include <fstream>
#include <niu2x/noncopyable.h>
#include <niu2x/type/std_alias.h>
#include <niu2x/type/convention.h>
#include <niu2x/fs/path.h>
#include <niu2x/fs/open_mode.h>
#include <niu2x/preprocess/class_utils.h>

namespace niu2x::fs {

enum class SeekPos {
    SET,
    CUR,
    END,
};

/**
 * @brief      This class describes a file.
 */
class NXAPI File : private Noncopyable {
public:
    /**
     * @brief      create file by path
     *
     * @param[in]  path  The path
     */
    explicit File(const Path& path);

    /**
     * @brief      create file by path
     *
     * @param      path  The path
     */
    explicit File(Path&& path);

    /**
     * @brief      is file exists
     *
     * @return     return true if file exists.
     */
    bool exists() const;

    /**
     * @brief      just like shell command "touch"
     */
    void touch() const;

    /**
     * @brief      just like shell command "mkdir"
     */
    void create_dir() const;

    /**
     * @brief      just like shell command "mkdir -p"
     */
    void ensure_dirs() const;

    /**
     * @brief      remove file
     */
    void remove() const;

    /**
     * @brief      get file's directory
     *
     * @return     return a new file object representing current file's
     * directory
     */
    File parent() const;

    /**
     * @brief      get file's path
     *
     * @return     return file's path
     */
    const Path& path() const { return path_; }

    /**
     * @brief      open this file
     *
     * @param[in]  open_mode  The open mode
     *
     * @return     return true if successful
     */
    bool open(OpenMode open_mode);

    /**
     * @brief      check if it is eof
     *
     * @return     return true if it is eof
     */
    bool eof() const;

    bool is_open() const { return !!fs_; }

    void seek(Offset offset, SeekPos seek_pos);
    void write(const void* data, NR size);
    NR read(void* data, NR max_size);

    NR size();

    Offset tell() const
    {
        check_file_opend();
        return fs_->tellg();
    }

    Buffer as_buffer(bool end_with_null = false);
    void close() { fs_.reset(); }

private:
    AbsPath path_;
    UniquePtr<std::fstream> fs_;
    void check_file_opend() const
    {
        if (!is_open()) {
            throw_runtime_err("File not open");
        }
    }
};

static_assert(type_pred::is_movable<File>);
static_assert(type_pred::is_not_copyable<File>);

} // namespace niu2x::fs

#endif