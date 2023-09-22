#ifndef NIU2X_COLOR_H
#define NIU2X_COLOR_H

#include <cstdint>
#include <niu2x/api.h>

namespace niu2x {

struct Color {
    union {

        struct {
            uint8_t r, g, b, a;
        };
        uint32_t rgba8;
    };

    Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a);
    Color();

    static const Color WHITE;
};

} // namespace niu2x

#endif