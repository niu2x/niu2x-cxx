#ifndef NXC_RAW_MEMORY_H
#define NXC_RAW_MEMORY_H

#include <nxc/api.h>
#include <nxc/utils.h>
#include <nxc/data.h>

namespace nxc {

template <size_t N>
class RawMemory : public Data {
public:
    RawMemory(uint8_t* data, size_t alloc);
    ~RawMemory();

    NXC_COPYABLE_DEFAULT(RawMemory);

protected:
    virtual uint8_t* _data() override { return data_; }
    virtual size_t _size() const override { return N; }

private:
    uint8_t data_[N];
};

} // namespace nxc

#endif