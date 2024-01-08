#ifndef NIU2X_MATH_SIZE_H
#define NIU2X_MATH_SIZE_H

#include <niu2x/std_alias.h>

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

    T area() const { return size.area(); }

    Rect intersection(const Rect& other) const
    {
        T x1 = max(origin.x, other.origin.x);
        T y1 = max(origin.y, other.origin.y);

        T x2 = min(origin.x + size.width, other.origin.x + other.size.width);
        T y2 = min(origin.y + size.height, other.origin.y + other.size.height);

        if (x2 >= x1 && y2 >= y1)
            return Rect(x1, y1, x2 - x1, y2 - y1);

        return Rect();
    }
};

using IntRect = Rect<int>;

} // namespace niu2x::math

#endif