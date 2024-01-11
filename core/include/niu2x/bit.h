#ifndef NIU2X_BIT_H
#define NIU2X_BIT_H

#include <bit>
#include <byteswap.h>

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

template <class T>
T bswap(T x)
{
    // this is never used
    // all T should be specialized
}

template <>
uint32_t bswap(uint32_t x)
{
    return bswap_32(x);
}

template <>
uint16_t bswap(uint16_t x)
{
    return bswap_16(x);
}

template <>
int16_t bswap(int16_t x)
{
    return bswap_16(x);
}

template <class T>
inline T le_to_host(T x)
{
    if (niu2x::endian::little) {
        return x;
    }
    return bswap<T>(x);
}

template <class T>
inline T be_to_host(T x)
{
    if (niu2x::endian::big) {
        return x;
    }
    return bswap<T>(x);
}

template <class T>
inline T net_to_host(T x)
{
    return be_to_host(x);
}

template <class T>
inline T host_to_le(T x)
{
    if (niu2x::endian::little) {
        return x;
    }
    return bswap<T>(x);
}

template <class T>
inline T host_to_be(T x)
{
    if (niu2x::endian::big) {
        return x;
    }
    return bswap<T>(x);
}

template <class T>
inline T host_to_net(T x)
{
    return host_to_be(x);
}

#endif