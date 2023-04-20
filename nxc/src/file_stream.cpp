#include "file_stream.h"

namespace nxc {

FileReadStream::FileReadStream(FilePtr file)
: file_(file)
, weak_file_(nullptr)
{
}

FileReadStream::FileReadStream(File* file)
: file_(nullptr)
, weak_file_(file)
{
}

FileReadStream::~FileReadStream() { _close_file(); }

Result<size_t> FileReadStream::_read(void* buf, size_t n)
{
    return (file_ ? file_.get() : weak_file_)->read(buf, n);
}
void FileReadStream::_close_file()
{
    (file_ ? file_.get() : weak_file_)->close();
}

FileWriteStream::FileWriteStream(FilePtr file)
: file_(file)
, weak_file_(nullptr)
{
}

FileWriteStream::FileWriteStream(File* file)
: file_(nullptr)
, weak_file_(file)
{
}
FileWriteStream::~FileWriteStream() { _close_file(); }

Result<size_t> FileWriteStream::_write(const void* buf, size_t n)
{
    return (file_ ? file_.get() : weak_file_)->write(buf, n);
}

void FileWriteStream::_close_file()
{
    (file_ ? file_.get() : weak_file_)->close();
}

} // namespace nxc
