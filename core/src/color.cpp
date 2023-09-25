#include <niu2x/type/color.h>
#include <niu2x/type/std_alias.h>

// #define NIU2X_COLOR_CLAMP(n) max(min((int)(n), 255), 0)

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

// Color::Color(const Vec3& c)
// : r(NIU2X_COLOR_CLAMP(c.x * 255))
// , g(NIU2X_COLOR_CLAMP(c.y * 255))
// , b(NIU2X_COLOR_CLAMP(c.z * 255))
// , a(255)
// {
// }

} // namespace niu2x