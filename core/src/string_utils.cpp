#include <niu2x/string_utils.h>
#include <niu2x/type/std_alias.h>

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

} // namespace niu2x::string_utils
