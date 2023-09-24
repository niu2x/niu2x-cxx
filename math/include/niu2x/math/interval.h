#ifndef NIU2X_MATH_INTERVAL_H
#define NIU2X_MATH_INTERVAL_H

#include <niu2x/math/constant.h>

namespace niu2x::math {

/**
 * @brief       区间 */
class Interval {
public:
    /**
     * @brief       默认构造一个空的区间，不包含任何数 */
    Interval()
    : min_(+infinity)
    , max_(-infinity)
    {
    }

    /**
     * @brief       按参数构建一个区间
     * @param       min   下界
     * @param       max   上界 */
    Interval(double min, double max)
    : min_(min)
    , max_(max)
    {
    }

    /**
     * @brief       判断按[闭]区间考虑的话，是否包含数字x
     * @param       x     一个数字
     * @return      如果包含x，返回true。否则返回false */
    bool contains(double x) const { return min_ <= x && x <= max_; }

    /**
     * @brief       判断按[开]区间考虑的话，是否包含数字x
     * @param       x     一个数字
     * @return      如果包含x，返回true。否则返回false */
    bool surrounds(double x) const { return min_ < x && x < max_; }

    /**
     * @brief       空区间
     */
    static const Interval empty;

    /**
     * @brief       (负无穷, 正无穷)
     */
    static const Interval universe;

private:
    double min_, max_;
};

} // namespace niu2x::math

#endif