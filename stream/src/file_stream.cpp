#include <niu2x/stream/file_stream.h>

namespace niu2x::stream {

FileByteReadStream::FileByteReadStream(const fs::File& file)
: file_(file, fs::OpenMode::READ)
{
}

FileByteReadStream::~FileByteReadStream() { }

size_t FileByteReadStream::read(uint8_t* buf, size_t size)
{
    file_.raw()->read(reinterpret_cast<char*>(buf), size);
    return file_.raw()->gcount();
}

bool FileByteReadStream::eof() { return file_.eof(); }

FileByteWriteStream::FileByteWriteStream(const fs::File& file)
: file_(file, fs::OpenMode::WRITE)
{
}

FileByteWriteStream::~FileByteWriteStream() { }

void FileByteWriteStream::write(const uint8_t* buf, size_t size)
{
    file_.raw()->write(reinterpret_cast<const char*>(buf), size);
}

} // namespace niu2x::stream