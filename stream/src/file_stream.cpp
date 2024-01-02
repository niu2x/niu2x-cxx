#include <niu2x/stream/file_stream.h>

namespace niu2x::stream {

FileReadStream::FileReadStream(const fs::File& file)
: file_(file, fs::OpenMode::READ)
{
}

FileReadStream::~FileReadStream() { }

size_t FileReadStream::read(uint8_t* buf, size_t size)
{
    file_.raw()->read(reinterpret_cast<char*>(buf), size);
    return file_.raw()->gcount();
}

bool FileReadStream::eof() { return file_.eof(); }

FileWriteStream::FileWriteStream(const fs::File& file)
: file_(file, fs::OpenMode::WRITE)
{
}

FileWriteStream::~FileWriteStream() { }

void FileWriteStream::write(const uint8_t* buf, size_t size)
{
    file_.raw()->write(reinterpret_cast<const char*>(buf), size);
}

} // namespace niu2x::stream