#include <niu2x/math.h>

namespace niu2x::math {

double hit_sphere(const Vec3& center, double radius, const Ray& r)
{
    auto oc = r.origin() - center;
    auto a = length2(r.direction());
    auto half_b = dot(oc, r.direction());
    auto c = length2(oc) - radius * radius;
    auto discriminant = half_b * half_b - a * c;

    if (discriminant < 0) {
        return -1.0;
    } else {
        return (-half_b - sqrt(discriminant)) / a;
    }
}

Color to_color(const Vec3& v)
{
    return Color(clamp((int)(v.x * 255), 0, 255),
        clamp((int)(v.y * 255), 0, 255), clamp((int)(v.z * 255), 0, 255), 255);
}

} // namespace niu2x::math
