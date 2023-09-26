#include <niu2x/stream/push_back_read_stream.h>

namespace niu2x::stream {

PushBackReadStream::PushBackReadStream(ReadStream* delegate)
: delegate_(delegate)
{
}
PushBackReadStream::~PushBackReadStream() { }

size_t PushBackReadStream::read(void* buf, size_t size)
{
    if (push_back_buffer_.size() > 0) {
        size = std::min(size, push_back_buffer_.size());
        memcpy(buf, push_back_buffer_.data(), size);
        push_back_buffer_.erase(
            push_back_buffer_.begin(), push_back_buffer_.begin() + size);
        return size;
    } else {
        return delegate_->read(buf, size);
    }
}

bool PushBackReadStream::eof()
{
    return push_back_buffer_.size() == 0 && delegate_->eof();
}

void PushBackReadStream::push_back(const void* buf, size_t size)
{

    auto old_size = push_back_buffer_.size();

    push_back_buffer_.resize(old_size + size);
    memcpy(push_back_buffer_.data() + old_size, buf, size);
}

} // namespace niu2x::stream