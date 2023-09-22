#ifndef NIU2X_COLOR_H
#define NIU2X_COLOR_H

#include <cstdint>
#include <niu2x/api.h>

namespace niu2x {

union NXAPI Color {
    struct {
        uint8_t r, g, b, a;
    };
    uint32_t rgba8;
};

} // namespace niu2x

#endif