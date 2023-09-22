#include <niu2x/type/color.h>
#include <niu2x/type/std_alias.h>

#define NIU2X_COLOR_CLAMP(n) max(min((int)(n), 255), 0)

namespace niu2x {

const Color Color::WHITE = Color(1.0, 1.0, 1.0, 1.0);

Color::Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
: r(r)
, g(g)
, b(b)
, a(a)
{
}

Color::Color()
: rgba8(0)
{
}

Color::Color(const ColorF c)
: r(NIU2X_COLOR_CLAMP(c.r * 255))
, g(NIU2X_COLOR_CLAMP(c.g * 255))
, b(NIU2X_COLOR_CLAMP(c.b * 255))
, a(255)
{
}

ColorF::ColorF(double r, double g, double b)
: r(r)
, g(g)
, b(b)
{
}

ColorF::ColorF()
: r(0)
, g(0)
, b(0)
{
}

} // namespace niu2x