#ifndef NIU2X_MATH_AABB_H
#define NIU2X_MATH_AABB_H

#include <niu2x/api.h>
#include <niu2x/disable_windows_warning.h>
#include <niu2x/math/constant.h>
#include <niu2x/math/utils.h>
#include <niu2x/math/interval.h>
#include <niu2x/math/linalg_alias.h>

namespace niu2x::math {

/**
 * @brief      Axis-Aligned Bounding Boxe
 */
class AABB {
public:
    Interval x, y, z;

    AABB() { }

    AABB(const Interval& ix, const Interval& iy, const Interval& iz)
    : x(ix)
    , y(iy)
    , z(iz)
    {
    }

    AABB(const Vec3& a, const Vec3& b)
    {
        // Treat the two points a and b as extrema for the bounding box, so we
        // don't require a particular minimum/maximum coordinate order.
        x = Interval(fmin(a[0], b[0]), fmax(a[0], b[0]));
        y = Interval(fmin(a[1], b[1]), fmax(a[1], b[1]));
        z = Interval(fmin(a[2], b[2]), fmax(a[2], b[2]));
    }

    const Interval& axis(int n) const
    {
        if (n == 1)
            return y;
        if (n == 2)
            return z;
        return x;
    }

    bool hit(const Ray& r, Interval ray_t) const
    {
        for (int a = 0; a < 3; a++) {
            auto tmp_r0 = (axis(a).min - r.origin()[a]) / r.direction()[a];
            auto tmp_r1 = (axis(a).max - r.origin()[a]) / r.direction()[a];
            auto t0 = fmin(tmp_r0, tmp_r1);
            auto t1 = fmax(tmp_r0, tmp_r1);
            ray_t.min = fmax(t0, ray_t.min);
            ray_t.max = fmin(t1, ray_t.max);
            if (ray_t.max <= ray_t.min)
                return false;
        }
        return true;
    }
};

} // namespace niu2x::math

#endif