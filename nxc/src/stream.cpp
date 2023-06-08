#define _CRT_SECURE_NO_WARNINGS

#include <nxc/stream.h>
#include <nxc/os.h>

namespace nxc {

FileReadStream::FileReadStream()
: fp_(nullptr)
{
}

FileReadStream::~FileReadStream() { close(); }

Result<void> FileReadStream::open(const String& path)
{
    NXC_ASSERT(!fp_, "fp_ is not nullptr.");
    fp_ = fopen(path.c_str(), "rb");
    return fp_ ? E::OK : OS::error();
}

void FileReadStream::close()
{
    if (fp_) {
        fclose(fp_);
        fp_ = nullptr;
    }
}

Result<size_t> FileReadStream::_pull(Char* buf, size_t count)
{
    NXC_ASSERT(fp_, "fp_ is not nullptr.");
    auto n = fread(buf, sizeof(Char), count, fp_);
    if (n)
        return n;
    if (feof(fp_))
        return E::END_OF_FILE;
    return E::ERROR;
}

} // namespace nxc