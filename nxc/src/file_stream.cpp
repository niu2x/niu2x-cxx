#define _CRT_SECURE_NO_WARNINGS

#include <nxc/file_stream.h>
#include <nxc/os.h>

namespace nxc {

FileReadStream::FileReadStream(const String& path)
: file_(path, OpenMode::READ)
{
}

FileReadStream::~FileReadStream() { }

Result<size_t> FileReadStream::_read_from_device(Char* buf, size_t count)
{
    auto n = fread(buf, sizeof(Char), count, file_.get());
    if (n)
        return n;
    if (feof(file_.get()))
        return E::END_OF_FILE;
    return E::ERROR;
}

static Result<FILE*> open(const String& path, OpenMode open_mode)
{
    auto* mode = open_mode == OpenMode::READ ? "rb" : "wb";
    auto fp = fopen(path.c_str(), mode);
    if (fp)
        return fp;
    return OS::error();
}

File::File(const String& path, OpenMode open_mode)
: Base(open(path, open_mode))
{
}

FileWriteStream::FileWriteStream(const String& path)
: file_(path, OpenMode::WRITE)
{
}

FileWriteStream::~FileWriteStream() { flush(); }

Result<size_t> FileWriteStream::_write_to_device(Char* ptr, size_t count)
{
    auto n = fwrite(ptr, sizeof(Char), count, file_.get());
    if (n)
        return n;
    return E::ERROR;
}

} // namespace nxc