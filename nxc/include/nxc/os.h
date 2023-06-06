#ifndef NXC_OS_H
#define NXC_OS_H

#include <nxc/api.h>
#include <nxc/utils.h>
#include <nxc/result.h>

namespace nxc {

// 没有标准跨平台实现的OS API
class NXC_API OS {
public:
    static Result<void> make_dir(const char* dirname);
    static Result<void> make_dirs(const char* pathname);
    static bool exist(const char* pathname);
    static bool is_dir(const char* pathname);
    const char path_sep;
};

} // namespace nxc

#endif