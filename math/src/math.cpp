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

} // namespace niu2x::math
