#ifndef NIU2X_MATH_SIZE_H
#define NIU2X_MATH_SIZE_H

namespace niu2x::math {

template <class T>
struct Size {
    T width;
    T height;

    T area() const { return width * height; }
};

using IntSize = Size<int>;
using DoubleSize = Size<double>;

template <class T>
struct Pos2D {
    T x, y;
};

template <class T>
struct Rect {
    Size<T> size;
    Pos2D<T> origin;
};

using IntRect = Rect<int>;

} // namespace niu2x::math

#endif