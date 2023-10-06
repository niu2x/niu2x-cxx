#include <niu2x/type/color.h>
#include <niu2x/type/std_alias.h>

namespace niu2x {

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