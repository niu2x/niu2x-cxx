#include <niu2x/math.h>

namespace niu2x::math {

Color to_color(const Vec3& v)
{
    return Color(clamp((int)(v.x * 255), 0, 255),
        clamp((int)(v.y * 255), 0, 255), clamp((int)(v.z * 255), 0, 255), 255);
}

} // namespace niu2x::math
