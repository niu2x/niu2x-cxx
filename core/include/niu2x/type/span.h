#ifndef NIU2X_SPAN_H
#define NIU2X_SPAN_H

#include <niu2x/type/convention.h>

namespace niu2x {

template <class T>

class Span {
public:
    Span();

    Span(T* base, size_t nr)
    : base_(base)
    , nr_(nr)
    {
    }

    template <size_t N>
    explicit Span(T (&array)[N])
    : base_(&array[0])
    , nr_(N)
    {
    }

    inline size_t size() const { return nr_; }
    inline T* data() const { return base_; }

    T& operator[](Index i) const { return base_[i]; }

private:
    T* base_ = nullptr;
    NR nr_ = 0;
};

} // namespace niu2x

#endif