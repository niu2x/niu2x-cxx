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
            auto invD = 1 / r.direction()[a];
            auto orig = r.origin()[a];

            auto t0 = (axis(a).min - orig) * invD;
            auto t1 = (axis(a).max - orig) * invD;

            if (invD < 0)
                swap(t0, t1);

            if (t0 > ray_t.min)
                ray_t.min = t0;
            if (t1 < ray_t.max)
                ray_t.max = t1;

            if (ray_t.max <= ray_t.min)
                return false;
        }
        return true;
    }

    AABB& operator+=(const AABB& p)
    {
        x = x + p.x;
        y = y + p.y;
        z = z + p.z;
        return *this;
    }

    AABB& operator*=(const AABB& p)
    {
        x = x * p.x;
        y = y * p.y;
        z = z * p.z;
        return *this;
    }

    AABB pad(double delta = 0.0001)
    {
        // Return an AABB that has no side narrower than some delta, padding if
        // necessary.
        auto new_x = (x.size() >= delta) ? x : x.expand(delta);
        auto new_y = (y.size() >= delta) ? y : y.expand(delta);
        auto new_z = (z.size() >= delta) ? z : z.expand(delta);

        return AABB(new_x, new_y, new_z);
    }
};

inline AABB operator+(const AABB& a, const AABB& b)
{
    return AABB(a.x + b.x, a.y + b.y, a.z + b.z);
}

inline AABB operator*(const AABB& a, const AABB& b)
{
    return AABB(a.x * b.x, a.y * b.y, a.z * b.z);
}

} // namespace niu2x::math

#endif