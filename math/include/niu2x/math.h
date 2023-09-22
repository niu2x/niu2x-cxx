#ifndef NIU2X_MATH_H
#define NIU2X_MATH_H

#include <niu2x/math/ray.h>
#include <niu2x/math/linalg_alias.h>

namespace niu2x::math {

template <class T>
T clamp(const T& n, const T& min, const T& max)
{
    if (n < min)
        return min;
    if (n > max)
        return max;
    return n;
}

} // namespace niu2x::math

#endif
