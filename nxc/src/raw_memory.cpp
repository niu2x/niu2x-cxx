#include <nxc/raw_memory.h>

namespace nxc {

RawMemory::RawMemory(uint8_t* data, size_t alloc)
: data_(data)
, data_alloc_(alloc)
{
}

RawMemory::~RawMemory() { }

} // namespace nxc