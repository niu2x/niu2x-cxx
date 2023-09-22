#include <niu2x/type/color.h>

namespace niu2x {

const Color Color::WHITE = Color(255, 255, 255, 255);

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

} // namespace niu2x