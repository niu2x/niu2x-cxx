#ifndef NIU2X_BIT_H
#define NIU2X_BIT_H

#include <bit>
#include <niu2x/api.h>

namespace niu2x::endian {

/**
 * @brief       is true if device is little-endian
 */
constexpr bool little = std::endian::native == std::endian::little;

/**
 * @brief       is true if device is big-endian
 */
constexpr bool big = std::endian::native == std::endian::big;

} // namespace niu2x::endian

#endif