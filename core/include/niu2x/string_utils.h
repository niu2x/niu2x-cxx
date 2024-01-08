#ifndef NIU2X_STRING_UTILS_H
#define NIU2X_STRING_UTILS_H

#include <niu2x/std_alias.h>

namespace niu2x::string_utils {

/**
 * @brief      split string by delimiter
 *
 * @param[in]  s          string to be split
 * @param[in]  delimiter  The delimiter
 *
 * @return     Vector of fields
 */
Vector<String> split(const String& s, char delimiter);

/**
 * @brief      convert u8string to u32string
 *
 * @param[in]  utf8  The utf8 string
 *
 * @return     Maybe<u32 string> object
 */
Maybe<UnicodeString> utf8_to_utf32(const String& utf8);

String lower(const String& s);
void lower(String* s);

} // namespace niu2x::string_utils

#endif