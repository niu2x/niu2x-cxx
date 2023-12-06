#include <niu2x/math.h>
#include <niu2x/painter/ray_trace/sphere.h>

namespace niu2x::painter::ray_trace {

Sphere::Sphere(
    const Vec3& center, double radius, const SharedPtr<Material>& mat)
: center_(center)
, center_vec_(math::vec3_zero)
, movable_(false)
, radius_(radius)
, mat_(mat)
{
    auto rvec = Vec3(radius, radius, radius);
    AABB box1(center - rvec, center + rvec);
    bbox_ = box1;
}

Sphere::Sphere(const Vec3& center, const Vec3& target_center, double radius,
    const SharedPtr<Material>& mat)
: center_(center)
, center_vec_(target_center - center)
, movable_(true)
, radius_(radius)
, mat_(mat)
{

    auto rvec = Vec3(radius, radius, radius);
    AABB box1(center - rvec, center + rvec);
    AABB box2(target_center - rvec, target_center + rvec);
    bbox_ = box1 + box2;
}

static void get_sphere_uv(const Vec3& p, double* u, double* v)
{
    auto theta = acos(-p.y);
    auto phi = atan2(-p.z, p.x) + math::pi;
    *u = phi / (2 * math::pi);
    *v = theta / math::pi;
}

static HitRecord make_hit_record(const Ray& ray, double t, const Vec3& center,
    double radius, const SharedPtr<Material>& mat, double sign)
{
    HitRecord record;
    record.p = ray.at(t);
    record.t = t;
    record.material = mat;
    record.set_normal(ray.direction(), normalize(record.p - center) * sign);

    Vec3 outward_normal = (record.p - center) / radius;
    get_sphere_uv(outward_normal, &record.u, &record.v);
    return record;
}

Maybe<HitRecord> Sphere::hit(const Ray& ray, const Interval& ray_interval) const
{
    auto my_center = movable_ ? center(ray.time()) : center_;
    auto oc = ray.origin() - my_center;
    auto a = length2(ray.direction());
    auto half_b = dot(oc, ray.direction());
    auto c = length2(oc) - radius_ * radius_;
    auto discriminant = half_b * half_b - a * c;

    if (discriminant >= 0) {
        double sqrtd = sqrt(discriminant);
        double root = (-half_b - sqrtd) / a;
        if (ray_interval.surrounds(root)) {
            return make_hit_record(
                ray, root, my_center, radius_, mat_, math::sign(radius_));
        } else {
            root = (-half_b + sqrtd) / a;
            if (ray_interval.surrounds(root)) {
                return make_hit_record(
                    ray, root, my_center, radius_, mat_, math::sign(radius_));
            }
        }
    }
    return null_maybe;
}

} // namespace niu2x::painter::ray_trace