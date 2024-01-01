#ifndef NIU2X_MATH_INTERVAL_H
#define NIU2X_MATH_INTERVAL_H

#include <niu2x/disable_windows_warning.h>
#include <niu2x/math/constant.h>
#include <niu2x/math/utils.h>

namespace niu2x::math {

/**
 * @brief       区间 */
struct Interval {
public:
    /**
     * @brief       默认构造一个空的区间，不包含任何数 */
    Interval()
    : min(+infinity)
    , max(-infinity)
    {
    }

    /**
     * @brief       按参数构建一个区间
     * @param       min   下界
     * @param       max   上界 */
    Interval(double min, double max)
    : min(min)
    , max(max)
    {
    }

    /**
     * @brief       判断按[闭]区间考虑的话，是否包含数字x
     * @param       x     一个数字
     * @return      如果包含x，返回true。否则返回false */
    bool contains(double x) const { return min <= x && x <= max; }

    /**
     * @brief       判断按[开]区间考虑的话，是否包含数字x
     * @param       x     一个数字
     * @return      如果包含x，返回true。否则返回false */
    bool surrounds(double x) const { return min < x && x < max; }

    /**
     * @brief       把x的值卡在这个区间里边
     * @param       x     一个数字
     * @return      如果x比min小，返回min。如果x比max大，返回max。否则返回x */
    double clamp(double x) const { return math::clamp(x, min, max); }

    /**
     * @brief      扩大一个区间
     *
     * @param[in]  delta 具体要扩大多少
     *
     * @return     扩大后的区间(min-delta/2, max+delta/2)
     */

    Interval expand(double delta) const
    {
        auto padding = delta / 2;
        return Interval(min - padding, max + padding);
    }

    double size() const { return max - min; }

    /**
     * @brief       空区间
     */
    static const Interval empty;

    /**
     * @brief       (负无穷, 正无穷)
     */
    static const Interval universe;

    double min, max;
};

inline Interval operator+(const Interval& a, const Interval& b)
{
    return Interval(fmin(a.min, b.min), fmax(a.max, b.max));
}

inline Interval operator*(const Interval& a, const Interval& b)
{
    return Interval(fmax(a.min, b.min), fmin(a.max, b.max));
}

} // namespace niu2x::math

#endif