#include <nxc/default_stream_factory.h>
#include "file_stream.h"
#include "buffer_stream.h"

namespace nxc {

ReadStreamPtr DefaultStreamFactory::create_read_stream(
    FilePtr file, bool auto_close_file)
{
    return NXC_MAKE_PTR(FileReadStream, file, auto_close_file);
}
WriteStreamPtr DefaultStreamFactory::create_write_stream(
    FilePtr file, bool auto_close_file)
{
    return NXC_MAKE_PTR(FileWriteStream, file, auto_close_file);
}

ReadStreamPtr DefaultStreamFactory::create_read_stream(const Buffer* buffer)
{
    NXC_ASSERT(buffer != nullptr, "buffer is nullptr");
    return NXC_MAKE_PTR(BufferReadStream, buffer);
}
WriteStreamPtr DefaultStreamFactory::create_write_stream(Buffer* buffer)
{
    NXC_ASSERT(buffer != nullptr, "buffer is nullptr");
    return NXC_MAKE_PTR(BufferWriteStream, buffer);
}

} // namespace nxc