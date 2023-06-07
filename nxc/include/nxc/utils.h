#ifndef NXC_UTILS_H
#define NXC_UTILS_H

#include <string.h>
#include <memory>
#include <type_traits>
#include <string>
#include <sstream>
#include <cmath>
#include <vector>
#include <functional>
#include <nxc/api.h>

#define NXC_LOG(...)                                                           \
    fprintf(stderr, __VA_ARGS__);                                              \
    fprintf(stderr, "\n");

#define NXC_INLINE inline

#define NXC_COPYABLE_DEFAULT(clazz)                                            \
    clazz(const clazz&) = default;                                             \
    clazz& operator=(const clazz&) = default;

#define NXC_MOVABLE_DEFAULT(clazz)                                             \
    clazz(clazz&&) = default;                                                  \
    clazz& operator=(clazz&&) = default;

// #define NXC_THROW(e) throw e;

#define NXC_ASSERT(cond, message)                                              \
    {                                                                          \
        if (!(cond)) {                                                         \
            NXC_ABORT(message);                                                \
        }                                                                      \
    }

namespace nxc {

template <class T>
using Vector = std::vector<T>;

template <class... T>
NXC_INLINE void unused(T&&...)
{
}

template <class... Args>
NXC_INLINE void do_nothing(Args&&...)
{
}

class NXC_API Noncopyable {
    
public:
    Noncopyable() {}
    ~Noncopyable() {}
    Noncopyable(const Noncopyable& other) = delete;
    Noncopyable& operator=(const Noncopyable& other) = delete;
};

template <class T>
using Function = std::function<T>;

using std::decay_t;
using std::forward;
using std::is_const_v;
using std::max;
using std::min;

// value
template <class T>
using Ptr = std::shared_ptr<T>;

template <class T>
class Singleton : private Noncopyable {
public:
    static T* get()
    {
        static T instance;
        return &instance;
    }

protected:
    Singleton() { }
    ~Singleton() { }
};

using String = std::string;

}; // namespace nxc

#define NXC_ABORT(...)                                                         \
    {                                                                          \
        NXC_LOG(__VA_ARGS__);                                                  \
        abort();                                                               \
    }

#define NXC_MALLOC(bytes)   (void*)(new uint8_t[bytes])
#define NXC_ALLOC(T, count) (T*)(new uint8_t[(count) * sizeof(T)])
#define NXC_FREE(ptr)       delete[](uint8_t*) ptr

#define NXC_NEW(T, ...)              new T(__VA_ARGS__)
#define NXC_NEW_ARRAY(T, count)      new T[count]
#define NXC_DELETE(ptr)              delete ptr
#define NXC_DELETE_ARRAY(ptr, count) delete[] ptr

#define NXC_NEW_AT(ptr, T, ...) new (ptr) T(__VA_ARGS__)
#define NXC_DELETE_AT(ptr, T)   (ptr)->~T()

template <class T>
NXC_INLINE T* NXC_PTR_OFFSET(T* ptr, ptrdiff_t off)
{
    return reinterpret_cast<T*>(off + (reinterpret_cast<uint8_t*>(ptr)));
}

namespace nxc {

template <class T>
void delete_ptr(T* ptr)
{
    NXC_DELETE(ptr);
}

} // namespace nxc

#define NXC_MAKE_PTR(T, ...)                                                   \
    nxc::Ptr<T>(NXC_NEW(T, __VA_ARGS__), nxc::delete_ptr<T>)

namespace nxc {

enum class OpenMode {
    READ,
    WRITE,
    RW,
};

using std::swap;

template <class T, class U>
T& COPY_AND_SWAP(T& self, U&& other)
{
    decay_t<T> tmp(forward<U>(other));
    swap(tmp, self);
    return self;
}

} // namespace nxc

#define NXC_MODULE_INIT_CLEANUP(setup, cleanup)                                \
    static class ____module_setup_cleanup {                                    \
    public:                                                                    \
        ____module_setup_cleanup(Function<void()> setup_delegate,              \
            Function<void()> cleanup_delegate)                                 \
        : setup_(setup_delegate)                                               \
        , cleanup_(cleanup_delegate)                                           \
        {                                                                      \
            setup_();                                                          \
        }                                                                      \
        ~____module_setup_cleanup() { cleanup_(); }                            \
                                                                               \
    private:                                                                   \
        Function<void()> setup_;                                               \
        Function<void()> cleanup_;                                             \
                                                                               \
    } ______(setup, cleanup);

#endif
