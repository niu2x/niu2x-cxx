#ifndef NIU2X_MATH_RAY_H
#define NIU2X_MATH_RAY_H

#include <niu2x/api.h>
#include <niu2x/type/std_alias.h>
#include <niu2x/math/linalg_alias.h>
#include <niu2x/disable_windows_warning.h>
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

} // namespace niu2x::math

#endif