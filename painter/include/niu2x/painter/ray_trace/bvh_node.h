#ifndef NIU2X_PAINTER_RAY_TRACE_BVH_H
#define NIU2X_PAINTER_RAY_TRACE_BVH_H

#include <niu2x/type.h>
#include <niu2x/math/utils.h>
#include "hittable.h"

namespace niu2x::painter::ray_trace {

class BVH_Node : public Hittable {
public:
    BVH_Node(const HittableGroup& group)
    : BVH_Node(group.objects(), 0, group.objects().size())
    {
    }

    BVH_Node(const Vector<SharedPtr<Hittable>>& src_objects, size_t start,
        size_t end)
    {
        auto objects = src_objects;

        int axis = math::random<int>(0, 2.99999);
        auto comparator = (axis == 0) ? box_x_compare
            : (axis == 1)             ? box_y_compare
                                      : box_z_compare;

        size_t object_span = end - start;

        if (object_span == 1) {
            left_ = right_ = objects[start];
        } else if (object_span == 2) {
            if (comparator(objects[start], objects[start + 1])) {
                left_ = objects[start];
                right_ = objects[start + 1];
            } else {
                left_ = objects[start + 1];
                right_ = objects[start];
            }
        } else {
            sort(objects.begin() + start, objects.begin() + end, comparator);

            auto mid = start + object_span / 2;
            left_ = make_shared<BVH_Node>(objects, start, mid);
            right_ = make_shared<BVH_Node>(objects, mid, end);
        }

        bbox_ = left_->bounding_box() + right_->bounding_box();
    }

    Maybe<HitRecord> hit(const Ray& r, const Interval& ray_t) const override
    {
        if (!bbox_.hit(r, ray_t))
            return maybe_null;

        auto hit_left = left_->hit(r, ray_t);
        auto hit_right = right_->hit(
            r, Interval(ray_t.min, hit_left ? hit_left.value().t : ray_t.max));

        return hit_right ?: hit_left;
    }

    AABB bounding_box() const override { return bbox_; }

    static bool box_compare(const SharedPtr<Hittable> a,
        const SharedPtr<Hittable> b, int axis_index)
    {
        return a->bounding_box().axis(axis_index).min
            < b->bounding_box().axis(axis_index).min;
    }

    static bool box_x_compare(
        const SharedPtr<Hittable> a, const SharedPtr<Hittable> b)
    {
        return box_compare(a, b, 0);
    }

    static bool box_y_compare(
        const SharedPtr<Hittable> a, const SharedPtr<Hittable> b)
    {
        return box_compare(a, b, 1);
    }

    static bool box_z_compare(
        const SharedPtr<Hittable> a, const SharedPtr<Hittable> b)
    {
        return box_compare(a, b, 2);
    }

private:
    SharedPtr<Hittable> left_;
    SharedPtr<Hittable> right_;
    AABB bbox_;
};

} // namespace niu2x::painter::ray_trace

namespace niu2x::painter {
using RayTraceBVH = ray_trace::BVH_Node;
}

#endif