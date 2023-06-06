#ifndef NXC_OS_H
#define NXC_OS_H

#include <nxc/api.h>
#include <nxc/utils.h>
#include <nxc/result.h>

namespace nxc {

class NXC_API OS : public Singleton<OS> {
public:
    OS();
    ~OS();
};

} // namespace nxc

#endif