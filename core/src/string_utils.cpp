#include <niu2x/string_utils.h>
#include <niu2x/std_alias.h>
#include "iconv.h"

namespace niu2x::string_utils {

Vector<String> split(const String& s, char delimiter)
{
    Vector<String> tokens;
    String token;
    std::istringstream tokenStream(s);
    while (std::getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

Maybe<UnicodeString> utf8_to_utf32(const String& utf8)
{
    return iconv::utf8_to_utf32(utf8);
}

} // namespace niu2x::string_utils
