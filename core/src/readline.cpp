#include <niu2x/readline.h>
#include "crossline.h"

namespace niu2x {

using namespace niu2x::thirdparty::crossline;

char* readline(const char* prompt, char* buf, int size)
{
    return crossline_readline(prompt, buf, size);
}

} // namespace niu2x