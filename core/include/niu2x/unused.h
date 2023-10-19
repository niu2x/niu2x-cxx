#ifndef NIU2X_UNUSED_H
#define NIU2X_UNUSED_H
/**
 * @brief       top most name space, contain all others
 */
namespace niu2x {

/**
 * @brief      silent compiler's warning about unused arguments
 *
 * @param[in]  <unnamed>  any argunemts
 */
inline void unused(...) { }

} // namespace niu2x

#endif