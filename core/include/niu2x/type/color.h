#ifndef NIU2X_COLOR_H
#define NIU2X_COLOR_H

#include <cstdint>
#include <niu2x/api.h>
#include <niu2x/disable_windows_warning.h>

namespace niu2x {

/**
 * @brief      RGBA Color, 8 bit per channel
 */
struct NXAPI Color {
    union {
        struct {
            uint8_t r, g, b, a;
        };
        uint32_t rgba8;
    };

    /**
     * @brief      constructor
     *
     * @param[in]  r     red
     * @param[in]  g     green
     * @param[in]  b     blue
     * @param[in]  a     alpha
     */
    Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a);

    /**
     * @brief      constructor that all bits is set to zero
     */
    Color();

    /**
     * white color
     */
    static const Color WHITE;
    /**
     * black color
     */
    static const Color BLACK;
};

} // namespace niu2x

#endif