#ifndef NIU2X_TYPE_BUFFER_H
#define NIU2X_TYPE_BUFFER_H

#include <niu2x/api.h>
#include <niu2x/type/std_alias.h>
#include <niu2x/preprocess/class_utils.h>

namespace niu2x {

class Buffer {
public:
    using MemBlock = Vector<uint8_t>;

    Buffer(size_t capacity = 0);
    ~Buffer();
    NIU2X_CLASS_DEFAULT_COPYABLE(Buffer);

    void write(const void* data, size_t size);
    size_t read(void* data, size_t size);

    void reset_write();
    void reset_read();

private:
    SharedPtr<MemBlock> buf_;
    size_t write_pos_;
    size_t read_pos_;
};

}; // namespace niu2x

#endif