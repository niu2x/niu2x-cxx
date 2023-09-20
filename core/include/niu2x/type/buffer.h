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

    void resize(size_t s) { buf_->resize(s); }

    String string() const { return String(buf_->begin(), buf_->end()); }

private:
    SharedPtr<MemBlock> buf_;
};

}; // namespace niu2x

#endif