#include <nxc/buffer.h>

namespace nxc {

static uint8_t init[1] = { 0 };

Buffer::Buffer(size_t alloc)
: Buffer()
{
    reserve(alloc);
}

Buffer::Buffer()
: data_(init)
, data_alloc_(0)
, data_nr_(0)
{
}

Buffer::~Buffer()
{
    if (data_ != init) {
        NXC_FREE(data_);
    }
}

void Buffer::write(const void* ptr, size_t n)
{
    reserve(size() + n);
    _write(ptr, n);
}

void Buffer::_write(const void* ptr, size_t n)
{
    memcpy(data_ + data_nr_, ptr, n);
    data_nr_ += n;
}

void Buffer::reserve(size_t c)
{
    if (c > data_alloc_) {
        auto new_data = (uint8_t*)NXC_MALLOC(c);
        if (data_ != init) {
            memcpy(new_data, data_, data_nr_);
            NXC_FREE(data_);
        }
        data_ = new_data;
        data_alloc_ = c;
    }
}

void Buffer::resize(size_t z, uint8_t default_value)
{
    reserve(z);
    _resize(z, default_value);
}

void Buffer::_resize(size_t new_nr, uint8_t default_value)
{
    if (new_nr > data_nr_) {
        memset(data_ + data_nr_, default_value, new_nr - data_nr_);
    }
    data_nr_ = new_nr;
}

Buffer::Buffer(const Buffer& other)
: data_(init)
, data_alloc_(0)
, data_nr_(0)
{
    if (other.data_nr_ > 0) {
        data_ = (uint8_t*)NXC_MALLOC(other.data_nr_);
        data_nr_ = data_alloc_ = other.data_nr_;
        memcpy(data_, other.data_, data_nr_);
    }
}

Buffer& Buffer::operator=(const Buffer& other)
{
    Buffer tmp(other);
    nxc::swap(tmp, *this);
    return *this;
}

Buffer::Buffer(Buffer&& other)
: data_(init)
, data_alloc_(0)
, data_nr_(0)
{
    swap(other);
}

Buffer& Buffer::operator=(Buffer&& other)
{
    Buffer tmp(std::move(other));
    std::swap(tmp, *this);
    return *this;
}

void Buffer::swap(Buffer& other) noexcept
{
    nxc::swap(other.data_, data_);
    nxc::swap(other.data_nr_, data_nr_);
    nxc::swap(other.data_alloc_, data_alloc_);
}

void swap(Buffer& a, Buffer& b) noexcept { a.swap(b); }

} // namespace nxc