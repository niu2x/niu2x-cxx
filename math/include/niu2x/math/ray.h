#ifndef NIU2X_MATH_RAY_H
#define NIU2X_MATH_RAY_H

#include <niu2x/std_alias.h>
#include <niu2x/math/linalg_alias.h>
#include <niu2x/disable_windows_warning.h>
#include <niu2x/math/interval.h>

namespace niu2x::math {

class Ray {
public:
    Ray() { }

    Ray(const Vec3& origin, const Vec3& direction)
    : origin_(origin)
    , dir_(normalize(direction))
    , time_(0)
    {
    }

    Ray(const Vec3& origin, const Vec3& direction, float time)
    : origin_(origin)
    , dir_(normalize(direction))
    , time_(time)
    {
    }

    inline const Vec3& origin() const { return origin_; }
    inline const Vec3& direction() const { return dir_; }
    inline Vec3 at(float t) const { return origin_ + t * dir_; }
    inline float time() const { return time_; }

private:
    Vec3 origin_;
    Vec3 dir_;
    float time_;
};

} // namespace niu2x::math

#endif