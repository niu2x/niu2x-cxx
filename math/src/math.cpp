#include <niu2x/disable_windows_warning.h>
#include <niu2x/math.h>

namespace niu2x::math {

Color to_color(const Vec3& v)
{
    return Color(static_cast<uint8_t>(clamp((int)(v.x * 255), 0, 255)),
        static_cast<uint8_t>(clamp((int)(v.y * 255), 0, 255)), static_cast<uint8_t>(clamp((int)(v.z * 255), 0, 255)), 255);
}

} // namespace niu2x::math
