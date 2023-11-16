#ifndef NIU2X_STRING_UTILS_H
#define NIU2X_STRING_UTILS_H

#include <niu2x/type/std_alias.h>

namespace niu2x::string_utils {

Vector<String> split(const String& s, char delimiter);

Maybe<String32> utf8_to_utf32(const String& utf8);

} // namespace niu2x::string_utils

#endif