#include <niu2x/type.h>

namespace niu2x {

Buffer::Buffer(size_t capacity)
: buf_(make_shared<MemBlock>())
, write_pos_(0)
, read_pos_(0)
{
    buf_->resize(capacity);
}

Buffer::~Buffer() { }

void Buffer::write(const void* data, size_t size)
{
    size_t new_size = size + write_pos_;
    if (new_size > buf_->size()) {
        buf_->resize(new_size);
    }
    memcpy(buf_->data() + write_pos_, data, size);
    write_pos_ += size;
}

size_t Buffer::read(void* data, size_t size)
{
    if (write_pos_ <= read_pos_)
        return 0;

    auto data_size = write_pos_ - read_pos_;
    size = std::min(data_size, size);

    if (size) {
        memcpy(data, buf_->data() + read_pos_, size);
        read_pos_ += size;
    }

    return size;
}

void Buffer::reset_write() { write_pos_ = 0; }
void Buffer::reset_read() { read_pos_ = 0; }

} // namespace niu2x