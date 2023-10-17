#ifndef NIU2X_MATH_LINALG_ALIAS_H
#define NIU2X_MATH_LINALG_ALIAS_H

#include <niu2x/math/linalg.h>

namespace niu2x::math {

using Vec3 = third_party::linalg::vec<double, 3>;
using Vec2 = third_party::linalg::vec<double, 2>;

inline const Vec3 vec3_zero = Vec3(0, 0, 0);
inline const Vec2 vec2_zero = Vec2(0, 0);

} // namespace niu2x::math

#endif
