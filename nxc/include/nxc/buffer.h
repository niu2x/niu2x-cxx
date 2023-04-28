#ifndef NXC_BUFFER_H
#define NXC_BUFFER_H

#include <nxc/api.h>
#include <nxc/utils.h>
#include <nxc/data.h>

namespace nxc {

// value
class NXC_API Buffer : public Data, private Noncopyable {
public:
    Buffer();
    Buffer(size_t alloc);

    Buffer(const Buffer& other);
    Buffer& operator=(const Buffer& other);

    Buffer(Buffer&& other);
    Buffer& operator=(Buffer&& other);

    ~Buffer();

    NXC_INLINE size_t capacity() const { return data_alloc_; }
    NXC_INLINE void clear() { data_nr_ = 0; }

    void write(const void* ptr, size_t n);

    void reserve(size_t c);
    void resize(size_t z, uint8_t default_value = 0);

    void swap(Buffer& other) noexcept;

protected:
    virtual uint8_t* _data() { return data_; }
    virtual size_t _size() const { return data_nr_; }

private:
    uint8_t* data_;
    size_t data_alloc_;
    size_t data_nr_;
    void _write(const void* ptr, size_t n);
    void _resize(size_t z, uint8_t default_value);
};

NXC_API void swap(Buffer& a, Buffer& b) noexcept;

} // namespace nxc

#endif