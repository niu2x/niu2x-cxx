#include <niu2x/math/ray.h>

namespace niu2x::math {

void HitRecord::set_normal(const Vec3& ray, const Vec3& p_normal)
{
    normal = p_normal;
    front_face = dot(normal, ray) < 0;
}

void HittableGroup::insert(SharedPtr<Hittable> ptr) { objs_.push_back(ptr); }

Maybe<HitRecord> HittableGroup::hit(
    const Ray& ray, const Interval& ray_interval) const
{

    Maybe<HitRecord> rec;
    auto closest_so_far = ray_interval;

    for (const auto& object : objs_) {
        auto hit = object->hit(ray, closest_so_far);

        if (hit) {
            closest_so_far.max = hit.value().t;
            rec = hit;
        }
    }

    return rec;
}

} // namespace niu2x::math