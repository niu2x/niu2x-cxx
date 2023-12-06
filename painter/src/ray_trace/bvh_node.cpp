#include <niu2x/painter/ray_trace/bvh_node.h>

namespace niu2x::painter::ray_trace {

BVH_Node::BVH_Node(
    const Vector<SharedPtr<Hittable>>& src_objects, size_t start, size_t end)
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

Maybe<HitRecord> BVH_Node::hit(const Ray& r, const Interval& ray_t) const
{
    if (!bbox_.hit(r, ray_t))
        return null_maybe;

    auto hit_left = left_->hit(r, ray_t);
    auto hit_right = right_->hit(
        r, Interval(ray_t.min, hit_left ? hit_left.value().t : ray_t.max));

    return hit_right ?: hit_left;
}

} // namespace niu2x::painter::ray_trace
