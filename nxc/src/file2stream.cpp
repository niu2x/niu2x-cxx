#include "file2stream.h"
#include "file_stream.h"

namespace nxc {

ReadStreamPtr create_read_stream(FilePtr file, bool auto_close_file)
{
    return NXC_MAKE_PTR(FileReadStream, file, auto_close_file);
}

WriteStreamPtr create_write_stream(FilePtr file, bool auto_close_file)
{
    return NXC_MAKE_PTR(FileWriteStream, file, auto_close_file);
}

} // namespace nxc
