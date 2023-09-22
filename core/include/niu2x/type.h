#ifndef NIU2X_TYPE_H
#define NIU2X_TYPE_H

#include <stdio.h>
#include <string.h>
#include <assert.h>

#include <cmath>
#include <bit>
#include <functional>

#include <niu2x/api.h>
#include <niu2x/config.h>
#include <niu2x/type/std_alias.h>
#include <niu2x/type/exception.h>
#include <niu2x/type/stream.h>
#include <niu2x/type/buffer.h>
#include <niu2x/type/serializable.h>
#include <niu2x/type/deserializable.h>
#include <niu2x/type/resource.h>
#include <niu2x/type/color.h>

namespace niu2x {
inline void unused(...) { }

} // namespace niu2x

#endif