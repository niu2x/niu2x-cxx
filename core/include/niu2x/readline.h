#ifndef NIU2X_READLINE_H
#define NIU2X_READLINE_H

#include <niu2x/api.h>

namespace niu2x {

NXAPI char* readline(const char* prompt, char* buf, int size);

} // namespace niu2x

#endif