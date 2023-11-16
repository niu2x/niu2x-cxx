#ifndef NIU2X_STRING_UTILS_ICONV_H
#define NIU2X_STRING_UTILS_ICONV_H

namespace niu2x::string_utils::iconv {

Maybe<String32> utf8_to_utf32(const String& utf8);

}

#endif