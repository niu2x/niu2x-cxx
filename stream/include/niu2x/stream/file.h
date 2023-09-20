#ifndef NIU2X_STREAM_FILE__H
#define NIU2X_STREAM_FILE__H

#include <niu2x/noncopyable.h>
#include <niu2x/preprocess/class_utils.h>
#include <niu2x/fs/open_mode.h>
#include <niu2x/fs/file.h>

namespace niu2x::stream {

using OpenMode = fs::OpenMode;
using Path = fs::Path;

class NXAPI File : private Noncopyable {
public:
    File(const fs::File& file, OpenMode open_mode);
    ~File();

    FILE* raw() { return fp_; }
    bool eof() const { return feof(fp_); }
    const Path& path() const { return path_; }

private:
    FILE* fp_;
    Path path_;
};

} // namespace niu2x::stream

#endif