#include "file_stream.h"

namespace nxc {

FileReadStream::FileReadStream(FilePtr file, bool auto_close_file)
: file_(file)
, should_close_(auto_close_file)
{
}

FileReadStream::~FileReadStream()
{
    if (should_close_)
        _close_file();
}

Result<size_t> FileReadStream::_read(void* buf, size_t n)
{
    return file_->read(buf, n);
}
void FileReadStream::_close_file() { file_->close(); }

FileWriteStream::FileWriteStream(FilePtr file, bool auto_close_file)
: file_(file)
, should_close_(auto_close_file)
{
}

FileWriteStream::~FileWriteStream()
{
    if (should_close_)
        _close_file();
}

Result<size_t> FileWriteStream::_write(const void* buf, size_t n)
{
    return file_->write(buf, n);
}

void FileWriteStream::_close_file() { file_->close(); }

} // namespace nxc
