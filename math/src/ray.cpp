#include <niu2x/math/ray.h>

namespace niu2x::math {

void HitRecord::set_normal(const Vec3& ray, const Vec3& normal)
{
    this->normal = normal;
    front_face = dot(normal, ray) < 0;
}

void HittableGroup::insert(SharedPtr<Hittable> ptr) { objs_.push_back(ptr); }

Optional<HitRecord> HittableGroup::hit(
    const Ray& ray, double min, double max) const
{

    Optional<HitRecord> rec;
    auto closest_so_far = max;

    for (const auto& object : objs_) {
        auto hit = object->hit(ray, min, closest_so_far);

        if (hit) {
            closest_so_far = hit.value().t;
            rec = hit;
        }
    }

    return rec;
}

} // namespace niu2x::math