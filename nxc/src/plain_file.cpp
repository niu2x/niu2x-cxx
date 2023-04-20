#include "plain_file.h"

namespace nxc {

PlainFile::PlainFile(const String& pathname)
: fp_(nullptr)
, pathname_(pathname)
{
}
PlainFile::~PlainFile() { close(); }

Result<void> PlainFile::_open(int mode)
{
    NXC_ASSERT(!fp_, "fp_ is not nullptr");
    mode_ = mode;
    fp_ = fopen(pathname_.c_str(),
        mode == O_READ ? "rb" : (mode == O_WRITE ? "wb" : "wb+"));
    return fp_ != nullptr ? E::OK : E::OS_ERROR;
}

void PlainFile::_close()
{
    if (fp_) {
        fclose(fp_);
        fp_ = nullptr;
    }
}

void PlainFile::_seek(int relative, size_t offset)
{
    NXC_ASSERT(fp_, "fp_ is nullptr");
    switch (relative) {
        case S_BEGIN: {
            fseek(fp_, offset, SEEK_SET);
            break;
        }
        case S_CURR: {
            fseek(fp_, offset, SEEK_CUR);
            break;
        }
        case S_END: {
            fseek(fp_, offset, SEEK_END);
            break;
        }
    }
}

size_t PlainFile::_tell() const
{
    NXC_ASSERT(fp_, "fp_ is nullptr");
    return ftell(fp_);
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

bool PlainFile::_readable() const
{
    NXC_ASSERT(fp_, "fp_ is nullptr");
    return mode_ & O_READ;
}
bool PlainFile::_writable() const
{
    NXC_ASSERT(fp_, "fp_ is nullptr");
    return mode_ & O_WRITE;
}

Ptr<PlainFile> PlainFile::create(const String& path)
{
    Ptr<PlainFile> file = NXC_MAKE_PTR(PlainFile, path);
    return file;
}

} // namespace nxc