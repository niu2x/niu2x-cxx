#include <niu2x/disable_windows_warning.h>
#include <niu2x/math/utils.h>

namespace niu2x::math {

static uint8_t color_component(double c)
{
    return static_cast<uint8_t>(clamp((int)(c * 255), 0, 255));
}

Color to_color(const Vec3& v)
{
    auto red = color_component(v.x);
    auto green = color_component(v.y);
    auto blue = color_component(v.z);
    return Color(red, green, blue, 255);
}

} // namespace niu2x::math
