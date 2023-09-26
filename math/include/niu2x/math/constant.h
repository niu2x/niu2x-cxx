#ifndef NIU2X_MATH_CONSTANT_H
#define NIU2X_MATH_CONSTANT_H

#include <limits>

namespace niu2x::math {

/**
 * @brief       max double value */
inline constexpr double max_double = std::numeric_limits<double>::max();
/**
 * @brief       infinity
 */
inline constexpr double infinity = std::numeric_limits<double>::infinity();

/**
 * @brief       PI
 */
inline constexpr double pi = 3.1415926535897932385;

} // namespace niu2x::math

#endif