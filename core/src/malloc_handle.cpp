#include <niu2x/type/malloc_handle.h>

namespace niu2x {

MallocHandle::MallocHandle(NR size)
{
    data_ = malloc(size);
    if (!data_) {
        throw BadAlloc();
    }
}
MallocHandle::~MallocHandle() { free(data_); }

MallocHandle::MallocHandle(MallocHandle&& other)
: data_(other.data_)
{
    other.data_ = nullptr;
}

MallocHandle& MallocHandle::operator=(MallocHandle&& other)
{
    swap(data_, other.data_);
    return *this;
}

} // namespace niu2x