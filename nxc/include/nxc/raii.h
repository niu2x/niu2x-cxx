#ifndef NXC_RAII_H
#define NXC_RAII_H

#include <nxc/utils.h>
#include <nxc/result.h>

namespace nxc {

template <class T, class ReleaseTr = Release<T>,
    class DefValueTr = DefalutValue<T>>
class RAII : private Noncopyable {
public:
    RAII()
    : res_(DefValueTr::value)
    {
    }

    ~RAII() { ReleaseTr::release(*res_); }

    NXC_INLINE const T& get() const { return *res_; }
    NXC_INLINE T& get() { return *res_; }

    NXC_INLINE void set(const T& t) { res_ = t; }
    NXC_INLINE operator bool() const { return res_; }
    NXC_INLINE Error error() const { return res_.error(); }

    RAII(RAII&& other)
    : res_(std::move(other.res_))
    {
        other.res_ = DefValueTr::value;
    }

protected:
    RAII(Result<T> t)
    : res_(std::move(t))
    {
    }

private:
    Result<T> res_;
};

} // namespace nxc

#endif