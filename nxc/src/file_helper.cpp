#include "file_helper.h"

namespace nxc {

using SeekPos = File::SeekPos;

int seek_flag(SeekPos relative)
{
    int flag = 0;
    switch (relative) {
        case SeekPos::BEGIN: {
            flag = SEEK_SET;
            break;
        }
        case SeekPos::CURR: {
            flag = SEEK_CUR;
            break;
        }
        case SeekPos::END: {
            flag = SEEK_END;
            break;
        }
    }
    return flag;
}

} // namespace nxc