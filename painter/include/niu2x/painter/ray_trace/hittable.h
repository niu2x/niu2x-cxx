#ifndef NIU2X_PAINTER_RAY_TRACE_HITTABLE_H
#define NIU2X_PAINTER_RAY_TRACE_HITTABLE_H

#include <niu2x/math/ray.h>
#include <niu2x/math/aabb.h>
#include <niu2x/painter/ray_trace/material.h>

namespace niu2x::painter::ray_trace {

using Ray = math::Ray;
using Interval = math::Interval;
using Vec3 = math::Vec3;
using Vec2 = math::Vec2;
using AABB = math::AABB;

struct NXAPI HitRecord {
    Vec3 p;
    Vec3 normal;
    double t;
    double u;
    double v;
    bool front_face;
    SharedPtr<Material> material;
    void set_normal(const Vec3& ray, const Vec3& normal);
};

class NXAPI Hittable {
public:
    virtual ~Hittable() = default;
    virtual Maybe<HitRecord> hit(
        const Ray& r, const Interval& ray_interval) const = 0;

    virtual AABB bounding_box() const = 0;
};

class NXAPI HittableGroup : public Hittable {
public:
    HittableGroup() = default;
    virtual ~HittableGroup() = default;

    void insert(SharedPtr<Hittable> ptr);

    virtual Maybe<HitRecord> hit(
        const Ray& r, const Interval& ray_interval) const override;

    virtual AABB bounding_box() const override { return bbox_; }

    const auto& objects() const { return objs_; }

private:
    Vector<SharedPtr<Hittable>> objs_;
    AABB bbox_;
};

} // namespace niu2x::painter::ray_trace

namespace niu2x::painter {
using RayTraceObjects = ray_trace::HittableGroup;
}

#endif