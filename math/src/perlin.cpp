#include <niu2x/math/perlin.h>

namespace niu2x::math {

double Perlin::noise(const Vec3& p) const
{
    auto u = p.x - floor(p.x);
    auto v = p.y - floor(p.y);
    auto w = p.z - floor(p.z);

    auto i = static_cast<int>(floor(p.x));
    auto j = static_cast<int>(floor(p.y));
    auto k = static_cast<int>(floor(p.z));
    Vec3 c[2][2][2];

    for (int di = 0; di < 2; di++)
        for (int dj = 0; dj < 2; dj++)
            for (int dk = 0; dk < 2; dk++)
                c[di][dj][dk] = ran_vec3_[perm_x_[(i + di) & 255]
                    ^ perm_y_[(j + dj) & 255] ^ perm_z_[(k + dk) & 255]];

    return trilinear_interp(c, u, v, w);
}

int* Perlin::Perlin_generate_perm()
{
    auto p = new int[point_count_];

    for (int i = 0; i < Perlin::point_count_; i++)
        p[i] = i;

    permute(p, point_count_);

    return p;
}

double Perlin::trilinear_interp(Vec3 c[2][2][2], double u, double v, double w)
{

    auto uu = u * u * (3 - 2 * u);
    auto vv = v * v * (3 - 2 * v);
    auto ww = w * w * (3 - 2 * w);
    double accum = 0;

    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 2; j++)
            for (int k = 0; k < 2; k++) {
                Vec3 weight_v(u - i, v - j, w - k);
                accum += (i * uu + (1 - i) * (1 - uu))
                    * (j * vv + (1 - j) * (1 - vv))
                    * (k * ww + (1 - k) * (1 - ww)) * dot(c[i][j][k], weight_v);
            }

    return accum;
}

void Perlin::permute(int* p, int n)
{
    for (int i = n - 1; i > 0; i--) {
        int target = random<int>(0, i);
        int tmp = p[i];
        p[i] = p[target];
        p[target] = tmp;
    }
}

} // namespace niu2x::math