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

} // namespace niu2x::math

#endif