#ifndef NIU2X_STREAM_FILE_STREAM_H
#define NIU2X_STREAM_FILE_STREAM_H

#include <niu2x/base_stream.h>
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

class FileByteReadStream : public ByteReadStream {
public:
    FileByteReadStream(const fs::File& file);
    virtual ~FileByteReadStream();
    virtual size_t read(uint8_t* buf, size_t size) override;
    virtual bool eof() override;

private:
    File file_;
};

class FileByteWriteStream : public ByteWriteStream {
public:
    FileByteWriteStream(const fs::File& file);
    virtual ~FileByteWriteStream();
    virtual void write(const uint8_t* buf, size_t size) override;

private:
    File file_;
};

} // namespace niu2x::stream

#endif