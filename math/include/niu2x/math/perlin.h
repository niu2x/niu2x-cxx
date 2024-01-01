#ifndef NIU2X_MATH_PERLIN_H
#define NIU2X_MATH_PERLIN_H

#include <limits>
#include <niu2x/math/linalg_alias.h>
#include <niu2x/noncopyable.h>
#include <niu2x/math/utils.h>
#include <niu2x/std_alias.h>

namespace niu2x::math {

class Perlin : private Noncopyable {
public:
    Perlin()
    {
        ran_vec3_ = new Vec3[point_count_];
        for (int i = 0; i < point_count_; ++i) {
            ran_vec3_[i] = random_unit_vec3();
        }

        perm_x_ = Perlin_generate_perm();
        perm_y_ = Perlin_generate_perm();
        perm_z_ = Perlin_generate_perm();
    }

    ~Perlin()
    {
        delete[] ran_vec3_;
        delete[] perm_x_;
        delete[] perm_y_;
        delete[] perm_z_;
    }

    double noise(const Vec3& p) const;

    double turb(const Vec3& p, int depth = 7) const
    {
        auto accum = 0.0;
        auto temp_p = p;
        auto weight = 1.0;

        for (int i = 0; i < depth; i++) {
            accum += weight * noise(temp_p);
            weight *= 0.5;
            temp_p *= 2;
        }

        return fabs(accum);
    }

private:
    static const int point_count_ = 256;
    Vec3* ran_vec3_;
    int* perm_x_;
    int* perm_y_;
    int* perm_z_;

    static int* Perlin_generate_perm();

    static double
    trilinear_interp(Vec3 c[2][2][2], double u, double v, double w);

    static void permute(int* p, int n);
};

static_assert(!type_pred::is_movable<Perlin>);

} // namespace niu2x::math

#endif