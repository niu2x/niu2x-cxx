#ifndef NIU2X_MALLOC_HANDLE_H
#define NIU2X_MALLOC_HANDLE_H

#include <niu2x/noncopyable.h>
#include <niu2x/convention.h>

namespace niu2x {

class MallocHandle : private Noncopyable {
public:
    MallocHandle(NR size);
    ~MallocHandle();

    MallocHandle(MallocHandle&& other);
    MallocHandle& operator=(MallocHandle&& other);

    void* data() const { return data_; }

    void swap(MallocHandle& other) noexcept;

private:
    void* data_;
};

inline void swap(MallocHandle& a, MallocHandle& b) noexcept { a.swap(b); }

} // namespace niu2x

#endif