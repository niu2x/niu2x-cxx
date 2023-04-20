#include "raw_memory_file.h"

namespace nxc {

RawMemoryFile::RawMemoryFile(ConstRawMemoryPtr memory)
: memory_(nullptr)
, const_memory_(memory)
, pos_(0)
, mode_(O_READ)
{
}

RawMemoryFile::RawMemoryFile(RawMemoryPtr memory)
: memory_(memory)
, const_memory_(memory)
, pos_(0)
, mode_(O_READ)
{
}

RawMemoryFile::~RawMemoryFile() { close(); }

// bool RawMemoryFile::_eof() const { return pos_ == const_memory_->size(); }

void RawMemoryFile::_seek(int relative, size_t offset)
{
    switch (relative) {
        case S_BEGIN: {
            pos_ = offset;
            break;
        }
        case S_CURR: {
            pos_ += offset;
            break;
        }
        case S_END: {
            pos_ = const_memory_->size() + offset;
            break;
        }
    }
}

size_t RawMemoryFile::_tell() const { return pos_; }

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

bool RawMemoryFile::_readable() const
{
    return mode_ == O_READ && (const_memory_);
}
bool RawMemoryFile::_writable() const { return mode_ == O_WRITE && memory_; }

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