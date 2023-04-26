#ifndef NXC_DATA_H
#define NXC_DATA_H

#include <nxc/api.h>
#include <nxc/utils.h>

namespace nxc {

class NXC_API Data {
public:
    Data() { }
    virtual ~Data() { }

    NXC_INLINE const uint8_t* data() const
    {
        return (const_cast<Data*>(this))->_data();
    }
    NXC_INLINE uint8_t* data() { return _data(); }
    NXC_INLINE size_t size() const { return _size(); }

protected:
    virtual uint8_t* _data() = 0;
    virtual size_t _size() const = 0;
};

} // namespace nxc

#endif