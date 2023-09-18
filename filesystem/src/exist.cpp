#include <niu2x/fs.h>
#include "build_time/build_config.h"

#if NIU2X_USE_POSIX
    #include <sys/types.h>
    #include <sys/stat.h>
    #include <unistd.h>
#endif

namespace niu2x::fs {

bool exist(const Path& path)
{
#if NIU2X_USE_POSIX
    return access(path.c_str(), F_OK) == 0;
#else
    return false;
#endif
}

} // namespace niu2x::fs