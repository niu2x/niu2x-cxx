#include <nxc/null_file.h>

namespace nxc {

NullFile::NullFile()
{
    fp_ = fopen("/dev/null", "rb");
    NXC_ASSERT(fp_, "/dev/null open fail");
}

NullFile::~NullFile() { fclose(fp_); }

} // namespace nxc