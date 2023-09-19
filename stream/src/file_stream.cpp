#include <niu2x/stream/file_stream.h>

namespace niu2x::stream {

FileReadStream::FileReadStream(const fs::File& file)
: file_(file, fs::OpenMode::READ)
{
}

FileReadStream::~FileReadStream() { }

size_t FileReadStream::read(void* buf, size_t size)
{
    return fread(buf, 1, size, file_.raw());
}

bool FileReadStream::eof() { return file_.eof(); }

FileWriteStream::FileWriteStream(const fs::File& file)
: file_(file, fs::OpenMode::WRITE)
{
}

FileWriteStream::~FileWriteStream() { }

void FileWriteStream::write(const void* buf, size_t size)
{
    if (fwrite(buf, 1, size, file_.raw()) != size) {
        throw_runtime_err("fwrite fail: " + file_.path().string());
    }
}

} // namespace niu2x::stream