#ifndef NXC_BUFFER_H
#define NXC_BUFFER_H

#include <nxc/api.h>
#include <nxc/utils.h>
#include <nxc/data.h>

namespace nxc {

class NXC_API Buffer : public Data, private Noncopyable {
public:
    Buffer();
    Buffer(size_t alloc);
    ~Buffer();

    NXC_INLINE size_t capacity() const { return data_alloc_; }
    NXC_INLINE void clear() { data_nr_ = 0; }

    void write(const void* ptr, size_t n);

    void reserve(size_t c);
    void resize(size_t z);

protected:
    virtual uint8_t* _data() { return data_; }
    virtual size_t _size() const { return data_nr_; }

private:
    uint8_t* data_;
    size_t data_alloc_;
    size_t data_nr_;
    void _write(const void* ptr, size_t n);
    void _resize(size_t z);
};

using BufferPtr = Ptr<Buffer>;
using ConstBufferPtr = Ptr<const Buffer>;

} // namespace nxc

#endif