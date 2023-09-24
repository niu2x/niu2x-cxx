#include <niu2x/math/interval.h>

namespace niu2x::math {

const Interval Interval::empty(+infinity, -infinity);

const Interval Interval::universe(-infinity, +infinity);

} // namespace niu2x::math
