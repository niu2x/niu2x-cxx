#include <niu2x/type/exception.h>
#include <string.h>
#include "build_time/build_config.h"

namespace niu2x {

void throw_os_err()
{
#if NIU2X_USE_POSIX
    char what[1024];
    auto e = errno;
    if (strerror_r(e, what, 1024)) {
        snprintf(what, 1024, "os err %d", e);
    }
    throw RuntimeError(what);
#else
    throw RuntimeError("unknown os err");
#endif
}

void throw_runtime_err(const String& err) { throw RuntimeError(err); }

} // namespace niu2x