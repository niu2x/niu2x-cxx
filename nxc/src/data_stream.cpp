#include "data_stream.h"

namespace nxc {

Result<size_t> DataReadStream::_read(void* buf, size_t n)
{
    auto available = data_.size() - pos_;
    n = min(available, n);

    if (!n)
        return E::END_OF_FILE;

    memcpy(buf, data_.data() + pos_, n);
    pos_ += n;

    return n;
}

DataReadStream::DataReadStream(const Data& data)
: data_(data)
, pos_(0)
{
}

DataReadStream::~DataReadStream() { }

Result<size_t> DataWriteStream::_write(const void* buf, size_t n)
{
    auto available = data_.size() - pos_;
    n = min(available, n);

    if (!n)
        return E::FULL_OF_FILE;

    memcpy(data_.data() + pos_, buf, n);
    pos_ += n;

    return n;
}

DataWriteStream::DataWriteStream(Data& data)
: data_(data)
, pos_(0)
{
}

DataWriteStream::~DataWriteStream() { }

} // namespace nxc