#include "file_stream.h"

namespace nxc {

FileReadStream::FileReadStream(FilePtr file)
: file_(file)
, weak_file_(nullptr)
, should_close_(false)
{
}

FileReadStream::FileReadStream(File* file)
: file_(nullptr)
, weak_file_(file)
, should_close_(false)
{
}

FileReadStream::~FileReadStream()
{
    if (should_close_)
        _close_file();
}

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
, should_close_(false)
{
}

FileWriteStream::FileWriteStream(File* file)
: file_(nullptr)
, weak_file_(file)
, should_close_(false)
{
}
FileWriteStream::~FileWriteStream()
{
    if (should_close_)
        _close_file();
}

Result<size_t> FileWriteStream::_write(const void* buf, size_t n)
{
    return (file_ ? file_.get() : weak_file_)->write(buf, n);
}

void FileWriteStream::_close_file()
{
    (file_ ? file_.get() : weak_file_)->close();
}

} // namespace nxc
