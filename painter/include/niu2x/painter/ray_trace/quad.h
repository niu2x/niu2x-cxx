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
        w_ = n / dot(n, n);

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
        Vec3 planar_hitpt_vector = intersection - Q_;
        auto alpha = dot(w_, cross(planar_hitpt_vector, v_));
        auto beta = dot(w_, cross(u_, planar_hitpt_vector));

        if (alpha < 0 || alpha > 1 || beta < 0 || beta > 1) {
            return maybe_null;
        }

        HitRecord rec;

        rec.u = alpha;
        rec.v = beta;

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
    Vec3 w_;
    double D_;
};
} // namespace niu2x::painter::ray_trace
#endif