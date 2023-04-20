#ifndef NXC_UTILS_H
#define NXC_UTILS_H

#include <string.h>
#include <memory>
#include <type_traits>
#include <string>
#include <cmath>
#include <vector>
#include <functional>
#include <boost/noncopyable.hpp>

#define NXC_INLINE BOOST_FORCEINLINE

#define NXC_COPYABLE_DEFAULT(clazz)                                            \
    clazz(const clazz&) = default;                                             \
    clazz& operator=(const clazz&) = default;

#define NXC_THROW(e) throw e;

#define NXC_ASSERT(cond, message)                                              \
    {                                                                          \
        if (!(cond)) {                                                         \
            NXC_ABORT(message);                                                \
        }                                                                      \
    }

namespace nxc {

template <class... T>
NXC_INLINE void unused(T&&...)
{
}

template <class... Args>
NXC_INLINE void do_nothing(Args&&...)
{
}

using Noncopyable = boost::noncopyable;

template <class T>
using Function = std::function<T>;

template <class T>
inline constexpr bool is_const_v = std::is_const_v<T>;

template <class T>
class Ptr {
public:
    using type = T;

    Ptr(T* obj, Function<void(T*)> del)
    : ptr_(obj, del)
    {
    }

    Ptr(std::nullptr_t n)
    : ptr_(n)
    {
    }

    Ptr()
    : ptr_()
    {
    }

    ~Ptr() { }

    NXC_COPYABLE_DEFAULT(Ptr)

    template <class U>
    Ptr(const Ptr<U>& other)
    {
        ptr_ = other.shared_ptr();
    }

    template <class U>
    NXC_INLINE Ptr& operator=(const Ptr<U>& other)
    {
        std::shared_ptr<T>::operator=(other);
        return *this;
    }
    NXC_INLINE bool readonly() const { return is_const_v<type>; }

    NXC_INLINE T* get() const { return ptr_.get(); }
    NXC_INLINE T* operator->() const { return ptr_.get(); }

    NXC_INLINE operator bool() const { return !!ptr_; }

    // user should not use it
    NXC_INLINE const std::shared_ptr<T>& shared_ptr() const { return ptr_; }

private:
    std::shared_ptr<T> ptr_;
};

using String = std::string;

template <class T1, class T2>
auto min(const T1& t1, const T2& t2)
{
    return std::min(t1, t2);
}

template <class T1, class T2>
auto max(const T1& t1, const T2& t2)
{
    return std::max(t1, t2);
}

class Exception : public std::exception {
public:
    Exception(const String& msg)
    : message_(msg)
    {
    }
    virtual ~Exception() { }
    virtual const char* what() const noexcept { return message_.c_str(); }

private:
    String message_;
};

}; // namespace nxc

#define NXC_ABORT(message) NXC_THROW(nxc::Exception(message))

#define NXC_MALLOC(bytes)   (void*)(new uint8_t[bytes])
#define NXC_ALLOC(T, count) (T*)(new uint8_t[(count) * sizeof(T)])
#define NXC_FREE(ptr)       delete[](uint8_t*) ptr

#define NXC_NEW(T, ...)              new T(__VA_ARGS__)
#define NXC_NEW_ARRAY(T, count)      new T[count]
#define NXC_DELETE(ptr)              delete ptr
#define NXC_DELETE_ARRAY(ptr, count) delete[] ptr

#define NXC_NEW_AT(ptr, T, ...) new (ptr) T(__VA_ARGS__)
#define NXC_DELETE_AT(ptr, T)   (ptr)->~T()

#define NXC_PTR_OFFSET(ptr, off) (void*)(off + ((uint8_t*)ptr))

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

template <class T>
class Iterator {
public:
    Iterator() { }
    virtual ~Iterator() { }
    virtual bool has_value() const = 0;
    virtual T& get() = 0;
    virtual void next() = 0;
};

template <class T>

class Vector {
public:
    class VectorIterator : public Iterator<T> {
    public:
        VectorIterator(std::vector<T>& backend)
        : backend_(backend)
        {
            it_ = backend_.begin();
        }

        virtual ~VectorIterator() { }
        virtual bool has_value() const override
        {
            return it_ != backend_.end();
        }
        virtual T& get() override { return *it_; }
        virtual void next() override { it_++; }
        friend class Vector<T>;

    private:
        std::vector<T>& backend_;
        typename std::vector<T>::iterator it_;
    };

    Vector() { }
    ~Vector() { }

    NXC_INLINE void push_back(const T& t) { backend_.push_back(t); }

    NXC_INLINE void erase(const T& t) { backend_.erase((t)); }
    NXC_INLINE void erase(const VectorIterator& iterator)
    {
        backend_.erase(iterator.it_);
    }

    NXC_INLINE size_t size() const { return backend_.size(); }

    VectorIterator walk() { return VectorIterator(backend_); }

private:
    std::vector<T> backend_;
};

enum FileOpenMode {
    O_READ = (1 << 0),
    O_WRITE = (1 << 1),
    O_RW = O_READ | O_WRITE,
};

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