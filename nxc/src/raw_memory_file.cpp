#include "raw_memory_file.h"

namespace nxc {

RawMemoryFile::RawMemoryFile(ConstRawMemoryPtr memory)
: memory_(nullptr)
, const_memory_(memory)
, pos_(0)
, mode_(OpenMode::READ)
{
}

RawMemoryFile::RawMemoryFile(RawMemoryPtr memory)
: memory_(memory)
, const_memory_(memory)
, pos_(0)
, mode_(OpenMode::READ)
{
}

RawMemoryFile::~RawMemoryFile() { }

Result<void> RawMemoryFile::_seek(SeekPos relative, long offset)
{
    switch (relative) {
        case SeekPos::BEGIN: {
            pos_ = offset;
            break;
        }
        case SeekPos::CURR: {
            pos_ += offset;
            break;
        }
        case SeekPos::END: {
            pos_ = const_memory_->size() + offset;
            break;
        }
    }
    return E::OK;
}

Result<long> RawMemoryFile::_tell() const { return pos_; }

Result<size_t> RawMemoryFile::_read(void* buf, size_t n)
{
    size_t avaiable = const_memory_->size() - pos_;

    if (!avaiable)
        return E::END_OF_FILE;

    size_t real = min(avaiable, n);

    memcpy(buf, const_memory_->data() + pos_, real);
    pos_ += real;

    return real;
}

Result<size_t> RawMemoryFile::_write(const void* buf, size_t n)
{
    size_t avaiable = memory_->size() - pos_;
    if (!avaiable)
        return E::FULL_OF_FILE;

    size_t real = min(avaiable, n);

    memcpy(memory_->data() + pos_, buf, real);
    pos_ += real;

    return real;
}

RawMemoryFilePtr RawMemoryFile::create(RawMemoryPtr memory)
{
    RawMemoryFilePtr file = NXC_MAKE_PTR(RawMemoryFile, memory);
    return file;
}

RawMemoryFilePtr RawMemoryFile::create(ConstRawMemoryPtr memory)
{
    RawMemoryFilePtr file = NXC_MAKE_PTR(RawMemoryFile, memory);
    return file;
}

} // namespace nxc