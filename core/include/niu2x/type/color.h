#ifndef NIU2X_COLOR_H
#define NIU2X_COLOR_H

#include <cstdint>
#include <niu2x/api.h>

namespace niu2x {

struct NXAPI ColorF {
    double r, g, b;

    ColorF();
    ColorF(double r, double g, double b);

    ColorF operator*(double scale)
    {
        return ColorF(r * scale, g * scale, b * scale);
    }

    ColorF operator+(const ColorF& other)
    {
        return ColorF(r + other.r, g + other.g, b + other.b);
    }
};

struct NXAPI Color {
    union {
        struct {
            uint8_t r, g, b, a;
        };
        uint32_t rgba8;
    };

    Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a);
    Color(const ColorF c);
    Color();

    static const Color WHITE;
};

} // namespace niu2x

#endif