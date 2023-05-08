#ifndef NXC_NULL_FILE_H
#define NXC_NULL_FILE_H

#include <nxc/utils.h>

namespace nxc {

class NXC_API NullFile : public Singleton<NullFile> {
public:
    NullFile();
    ~NullFile();

    NXC_INLINE FILE* c_file() const { return fp_; }

private:
    FILE* fp_;
};

} // namespace nxc

#endif