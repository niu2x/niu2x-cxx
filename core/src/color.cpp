#include <niu2x/type/color.h>

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
: : r(c.r * 255)
    , g(c.g * 255)
    , b(c.b * 255)
    , a(255)
{
}

} // namespace niu2x