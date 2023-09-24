#ifndef NIU2X_MATH_RAY_H
#define NIU2X_MATH_RAY_H

#include <niu2x/api.h>
#include <niu2x/type/std_alias.h>
#include <niu2x/math/linalg_alias.h>
#include <niu2x/math/interval.h>

namespace niu2x::math {

class NXAPI Ray {
public:
    Ray() { }

    Ray(const Vec3& origin, const Vec3& direction)
    : origin_(origin)
    , dir_(direction)
    {
    }

    Vec3 origin() const { return origin_; }
    Vec3 direction() const { return dir_; }

    Vec3 at(double t) const { return origin_ + t * dir_; }

private:
    Vec3 origin_;
    Vec3 dir_;
};

struct NXAPI HitRecord {
    Vec3 p;
    Vec3 normal;
    double t;
    bool front_face;

    void set_normal(const Vec3& ray, const Vec3& normal);
};

class NXAPI Hittable {
public:
    virtual ~Hittable() = default;
    virtual Maybe<HitRecord> hit(
        const Ray& r, const Interval& ray_interval) const = 0;
};

class NXAPI HittableGroup : public Hittable {
public:
    HittableGroup() = default;
    virtual ~HittableGroup() = default;

    void insert(SharedPtr<Hittable> ptr);

    virtual Maybe<HitRecord> hit(
        const Ray& r, const Interval& ray_interval) const override;

private:
    Vector<SharedPtr<Hittable>> objs_;
};

} // namespace niu2x::math

#endif