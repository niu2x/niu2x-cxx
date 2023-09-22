#ifndef NIU2X_TYPE_BUFFER_H
#define NIU2X_TYPE_BUFFER_H

#include <niu2x/api.h>
#include <niu2x/type/std_alias.h>
#include <niu2x/preprocess/class_utils.h>

namespace niu2x {

class Buffer {
public:
    using MemBlock = Vector<uint8_t>;

    Buffer(size_t size = 0);
    ~Buffer();
    NIU2X_CLASS_DEFAULT_COPYABLE(Buffer);

    void write(const void* data, off_t offset, size_t size);
    void read(void* data, off_t offset, size_t size) const;

    size_t size() const { return buf_->size(); }

    const uint8_t* data() const { return buf_->data(); }

    uint8_t* data() { return buf_->data(); }

    void resize(size_t s) { buf_->resize(s); }

    String str() const { return String(buf_->begin(), buf_->end()); }

private:
    SharedPtr<MemBlock> buf_;
};

}; // namespace niu2x

#endif