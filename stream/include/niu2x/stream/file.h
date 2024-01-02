#ifndef NIU2X_STREAM_FILE__H
#define NIU2X_STREAM_FILE__H

#include <fstream>
#include <niu2x/noncopyable.h>
#include <niu2x/fs/open_mode.h>
#include <niu2x/fs/file.h>

namespace niu2x::stream {

using OpenMode = fs::OpenMode;
using Path = fs::AbsPath;

class File : private Noncopyable {
public:
    File(const fs::File& file, OpenMode open_mode);
    ~File();

    std::fstream* raw() { return &fp_; }
    bool eof() const { return fp_.eof(); }
    const Path& path() const { return path_; }

private:
    std::fstream fp_;
    Path path_;
};

} // namespace niu2x::stream

#endif