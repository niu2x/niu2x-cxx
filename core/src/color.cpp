#include <niu2x/color.h>

namespace niu2x {

Color4B::Color4B(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
: r(r)
, g(g)
, b(b)
, a(a)
{
}

Color4B::Color4B()
: rgba8(0)
{
}

#if NIU2X_USE_THREE_WAY_COMPARE
auto Color4B::operator<=>(const Color4B& c) const { return rgba8 <=> c.rgba8; }
#endif

bool Color4B::operator==(const Color4B& c) const { return rgba8 == c.rgba8; }

Color4F::Color4F()
: r(0)
, g(0)
, b(0)
, a(0)
{
}

Color4F::Color4F(float channels[])
: r(channels[0])
, g(channels[1])
, b(channels[2])
, a(channels[3])
{
}
Color4F::Color4F(float r, float g, float b, float a)
: r(r)
, g(g)
, b(b)
, a(a)
{
}

} // namespace niu2x