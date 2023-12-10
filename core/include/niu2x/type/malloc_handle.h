#ifndef NIU2X_MALLOC_HANDLE_H
#define NIU2X_MALLOC_HANDLE_H

#include <niu2x/noncopyable.h>
#include <niu2x/type/convention.h>

namespace niu2x {

class MallocHandle : private Noncopyable {
public:
    MallocHandle(NR size);
    ~MallocHandle();

    MallocHandle(MallocHandle&& other);
    MallocHandle& operator=(MallocHandle&& other);

    void* data() const { return data_; }

private:
    void* data_;
};

} // namespace niu2x

#endif