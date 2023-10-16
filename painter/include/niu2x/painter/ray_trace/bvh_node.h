#ifndef NIU2X_PAINTER_RAY_TRACE_BVH_H
#define NIU2X_PAINTER_RAY_TRACE_BVH_H

#include <niu2x/type.h>
#include <niu2x/math/utils.h>
#include "hittable.h"

namespace niu2x::painter::ray_trace {

class BVH_Node : public Hittable {
public:
    using HittableList = Vector<SPtr<Hittable>>;

    BVH_Node(const HittableGroup& group)
    : BVH_Node(group.objects(), 0, group.objects().size())
    {
    }

    BVH_Node(const HittableList& src_objects, size_t start, size_t end);

    Maybe<HitRecord> hit(const Ray& r, const Interval& ray_t) const override;

    AABB bounding_box() const override { return bbox_; }

    static bool box_compare(
        const SPtr<Hittable> a, const SPtr<Hittable> b, int axis_index)
    {
        return a->bounding_box().axis(axis_index).min
            < b->bounding_box().axis(axis_index).min;
    }

    static bool box_x_compare(const SPtr<Hittable> a, const SPtr<Hittable> b)
    {
        return box_compare(a, b, 0);
    }

    static bool box_y_compare(const SPtr<Hittable> a, const SPtr<Hittable> b)
    {
        return box_compare(a, b, 1);
    }

    static bool box_z_compare(const SPtr<Hittable> a, const SPtr<Hittable> b)
    {
        return box_compare(a, b, 2);
    }

private:
    SPtr<Hittable> left_;
    SPtr<Hittable> right_;
    AABB bbox_;
};

} // namespace niu2x::painter::ray_trace

namespace niu2x::painter {
using RayTraceBVH = ray_trace::BVH_Node;
}

#endif