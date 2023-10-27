#ifndef NIU2X_PAINTER_RAY_TRACE_QUAD_H
#define NIU2X_PAINTER_RAY_TRACE_QUAD_H

#include <niu2x/math.h>
#include <niu2x/unused.h>
#include <niu2x/painter/ray_trace/hittable.h>

namespace niu2x::painter::ray_trace {
class Quad : public Hittable {
public:
    Quad(const Vec3& _Q, const Vec3& _u, const Vec3& _v, SPtr<Material> m)
    : Q_(_Q)
    , u_(_u)
    , v_(_v)
    , mat_(m)
    {

        auto n = cross(u_, v_);
        normal_ = normalize(n);
        D_ = dot(normal_, Q_);

        set_bounding_box();
    }

    virtual void set_bounding_box() { bbox_ = AABB(Q_, Q_ + u_ + v_).pad(); }

    AABB bounding_box() const override { return bbox_; }

    Maybe<HitRecord> hit(const Ray& r, const Interval& ray_t) const override
    {
        auto denom = dot(normal_, r.direction());

        // No hit if the ray is parallel to the plane.
        if (fabs(denom) < 1e-8)
            return maybe_null;

        // Return false if the hit point parameter t is outside the ray
        // interval.
        auto t = (D_ - dot(normal_, r.origin())) / denom;
        if (!ray_t.contains(t))
            return maybe_null;

        auto intersection = r.at(t);

        HitRecord rec;

        rec.t = t;
        rec.p = intersection;
        rec.material = mat_;
        rec.set_normal(r.direction(), normal_);

        return rec;
    }

private:
    Vec3 Q_;
    Vec3 u_, v_;
    SPtr<Material> mat_;
    AABB bbox_;
    Vec3 normal_;
    double D_;
};
} // namespace niu2x::painter::ray_trace
#endif