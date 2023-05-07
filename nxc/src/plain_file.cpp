#define _CRT_SECURE_NO_WARNINGS

#include "plain_file.h"
#include "file_helper.h"

namespace nxc {

static const char* file_mode(OpenMode mode)
{
    NXC_ASSERT(mode == OpenMode::READ || mode == OpenMode::WRITE,
        "unsupport open mode");
    switch (mode) {
        case OpenMode::READ:
            return "rb";
        case OpenMode::WRITE:
            return "wb";
    }
    return "";
}

PlainFile::PlainFile(const String& pathname)
: fp_(nullptr)
, pathname_(pathname)
{
}
PlainFile::~PlainFile() { NXC_ASSERT(fp_ == nullptr, "file is not closed"); }

Result<void> PlainFile::_open(OpenMode mode)
{
    NXC_ASSERT(!fp_, "fp_ is not nullptr");
    mode_ = mode;
    fp_ = fopen(pathname_.c_str(), file_mode(mode_));
    return fp_ != nullptr ? E::OK : E::OS_ERROR;
}

void PlainFile::_close()
{
    if (fp_) {
        fclose(fp_);
        fp_ = nullptr;
    }
}

Result<void> PlainFile::_seek(SeekPos relative, long offset)
{
    NXC_ASSERT(fp_, "fp_ is nullptr");
    auto flag = seek_flag(relative);
    if (!fseek(fp_, offset, flag))
        return E::OK;
    else
        return E::OS_ERROR;
}

Result<long> PlainFile::_tell() const
{
    NXC_ASSERT(fp_, "fp_ is nullptr");
    long pos = ftell(fp_);
    if (pos < 0)
        return E::OS_ERROR;
    return pos;
}

Result<size_t> PlainFile::_read(void* buf, size_t n)
{
    NXC_ASSERT(fp_, "fp_ is nullptr");
    auto ret = fread(buf, 1, n, fp_);
    if (!ret) {
        if (feof(fp_))
            return E::END_OF_FILE;
        if (ferror(fp_))
            return E::OS_ERROR;
    }
    return ret;
}

Result<size_t> PlainFile::_write(const void* buf, size_t n)
{
    NXC_ASSERT(fp_, "fp_ is nullptr");
    auto ret = fwrite(buf, 1, n, fp_);
    if (ret < n) {
        if (ferror(fp_))
            return E::OS_ERROR;
    }
    return ret;
}

Ptr<PlainFile> PlainFile::create(const String& path)
{
    Ptr<PlainFile> file = NXC_MAKE_PTR(PlainFile, path);
    return file;
}

} // namespace nxc