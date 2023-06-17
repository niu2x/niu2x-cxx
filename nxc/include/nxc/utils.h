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

namespace nxc {

template <class T>
struct DefalutValue {
};

template <class T>
struct Release {
};

template <class T>
struct DefalutValue<T*> {
    static T* const value = nullptr;
};

} // namespace nxc

namespace nxc {

template <typename... U>
struct all_integral : std::conjunction<std::is_integral<U>...> {
};

template <class T>
class Bitmask {
public:
    Bitmask()
    : value_(0)
    {
    }
    explicit Bitmask(T mask)
    : value_(mask)
    {
    }

    ~Bitmask() { }

    template <class... U>
    NXC_INLINE static std::enable_if_t<all_integral<U...>::value, Bitmask>
    from_bit(int first, U... others)
    {
        return from_bit(first) | from_bit(others...);
    }

    NXC_INLINE static Bitmask from_bit(int n) { return Bitmask(bitmask(n)); }

    static const Bitmask Zero;

    NXC_INLINE T get() const { return value_; }
    NXC_INLINE void set(T v) { value_ = v; }

    NXC_INLINE friend Bitmask operator|(const Bitmask& a, const Bitmask& b)
    {
        return Bitmask(a.value_ | b.value_);
    }

    NXC_INLINE friend Bitmask operator&(const Bitmask& a, const Bitmask& b)
    {
        return Bitmask(a.value_ & b.value_);
    }

    NXC_INLINE void set_bit(int n) { value_ |= bitmask(n); }

    NXC_INLINE void reset_bit(int n) { value_ &= ~bitmask(n); }

    NXC_INLINE bool test_bit(int n) const { return bitmask(n) & value_; }

    NXC_INLINE bool operator==(const Bitmask& other) const
    {
        return value_ == other.value_;
    }

private:
    T value_;

    NXC_INLINE static T bitmask(int n) { return 1 << (n); }
};

template <class T>
const Bitmask<T> Bitmask<T>::Zero = Bitmask<T>(0);

}; // namespace nxc

#endif
