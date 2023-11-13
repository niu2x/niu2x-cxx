#include <niu2x/string_utils.h>

namespace string_utils {

Vector<String> split(const String& s, char delimiter)
{
    Vector<::string> tokens;
    String token;
    std::istringstream tokenStream(s);
    while (std::getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

} // namespace string_utils
