#ifndef NIU2X_MATH_SIZE_H
#define NIU2X_MATH_SIZE_H

#include <niu2x/type/std_alias.h>

namespace niu2x::math {

template <class T>
struct Size {
    T width = 0;
    T height = 0;

    T area() const { return width * height; }

    template <class U>
    operator Size<U>() const
    {
        return { static_cast<U>(width), static_cast<U>(height) };
    }
};

using IntSize = Size<int>;
using RealSize = Size<double>;
using DoubleSize = RealSize;

template <class T>
struct Pos2D {
    T x = 0, y = 0;
};

template <class T>
struct Rect {
    Size<T> size;
    Pos2D<T> origin;

    Rect(T x, T y, T w, T h)
    {
        origin = { x, y };
        size = { w, h };
    }

    Rect()
    {
        origin = { 0, 0 };
        size = { 0, 0 };
    }
};

using IntRect = Rect<int>;

} // namespace niu2x::math

#endif