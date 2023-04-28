#ifndef NXC_RAW_MEMORY_H
#define NXC_RAW_MEMORY_H

#include <nxc/api.h>
#include <nxc/utils.h>
#include <nxc/data.h>

namespace nxc {

class NXC_API RawMemory : public Data {
public:
    RawMemory(uint8_t* data, size_t alloc);
    ~RawMemory();

    NXC_COPYABLE_DEFAULT(RawMemory);

protected:
    virtual uint8_t* _data() override { return data_; }
    virtual size_t _size() const override { return data_alloc_; }

private:
    uint8_t* data_;
    size_t data_alloc_;
};

} // namespace nxc

#endif