#ifndef NXC_OS_H
#define NXC_OS_H

#include <nxc/api.h>
#include <nxc/utils.h>

namespace nxc {

class NXC_API OS : public Singleton<OS> {
public:
    OS();
    virtual ~OS();
    ResultVoid make_dirs(const String& pathname);
    void ensure_dirs(const String& pathname);
    bool exist(const String& pathname);
    bool is_dir(const String& pathname);
    bool is_file(const String& pathname);
};

} // namespace nxc

#endif