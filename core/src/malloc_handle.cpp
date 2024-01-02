#include <niu2x/malloc_handle.h>
#include <niu2x/std_alias.h>

namespace niu2x {

MallocHandle::MallocHandle(NR size)
{
    data_ = malloc(size);
    if (!data_) {
        throw BadAlloc();
    }
}
MallocHandle::~MallocHandle()
{
    if (data_)
        free(data_);
}

MallocHandle::MallocHandle(MallocHandle&& other)
: data_(other.data_)
{
    other.data_ = nullptr;
}

MallocHandle& MallocHandle::operator=(MallocHandle&& other)
{
    MallocHandle tmp(move(other));
    swap(tmp);
    return *this;
}

void MallocHandle::swap(MallocHandle& other) noexcept
{
    niu2x::swap(data_, other.data_);
}

} // namespace niu2x