#ifndef NIU2X_MATH_LINALG_ALIAS_H
#define NIU2X_MATH_LINALG_ALIAS_H

#include <niu2x/math/linalg.h>

namespace niu2x::math {

namespace linalg = third_party::linalg;

template <class T, int N>
using Vec = linalg::vec<T, N>;

template <class T, int M, int N>
using Mat = linalg::mat<T, M, N>;

using Vec3 = Vec<float, 3>;
using Vec2 = Vec<float, 2>;
using Mat4 = Mat<float, 4, 4>;

template <class T>
using CVec3 = const Vec<T, 3>;

template <class T>
Mat<T, 4, 4> scaling_matrix(CVec3<T>& scale)
{
    return linalg::scaling_matrix(scale);
}

template <class T>
Mat<T, 4, 4> translation_matrix(CVec3<T>& t)
{
    return linalg::translation_matrix(t);
}

template <class T>
Mat<T, 4, 4> lookat_matrix(CVec3<T>& eye, CVec3<T>& center, CVec3<T>& up)
{
    return linalg::lookat_matrix(eye, center, up);
}

template <class T>
Mat<T, 4, 4> frustum_matrix(T x0, T x1, T y0, T y1, T n, T f)
{
    auto delta_x = x1 - x0;
    auto delta_y = y1 - y0;
    return {
        { 2 / delta_x, 0, 0, 0 },
        { 0, 2 / delta_y, 0, 0 },
        { 0, 0, -2 / (f - n), 0 },
        { -(x1 + x0) / delta_x, -(y1 + y0) / delta_y, -(f + n) / (f - n), 1 },
    };
}

} // namespace niu2x::math

#endif
