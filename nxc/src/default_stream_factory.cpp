#include <nxc/default_stream_factory.h>
#include "file_stream.h"
#include "buffer_stream.h"

namespace nxc {

ReadStreamPtr DefaultStreamFactory::create_read_stream(FilePtr file)
{
    NXC_ASSERT(file->readable(), "file is not readable");
    return NXC_MAKE_PTR(FileReadStream, file);
}
WriteStreamPtr DefaultStreamFactory::create_write_stream(FilePtr file)
{
    NXC_ASSERT(file->writable(), "file is not writable");
    return NXC_MAKE_PTR(FileWriteStream, file);
}

ReadStreamPtr DefaultStreamFactory::create_read_stream(File* file)
{
    NXC_ASSERT(file->readable(), "file is not readable");
    return NXC_MAKE_PTR(FileReadStream, file);
}

ReadStreamPtr DefaultStreamFactory::create_read_stream(const Buffer* buffer)
{
    NXC_ASSERT(buffer != nullptr, "buffer is not readable");

    return NXC_MAKE_PTR(BufferReadStream, buffer);
}
WriteStreamPtr DefaultStreamFactory::create_write_stream(Buffer* buffer)
{
    NXC_ASSERT(buffer != nullptr, "buffer is not readable");
    return NXC_MAKE_PTR(BufferWriteStream, buffer);
}

WriteStreamPtr DefaultStreamFactory::create_write_stream(File* file)
{
    NXC_ASSERT(file->writable(), "file is not readable");
    return NXC_MAKE_PTR(FileWriteStream, file);
}

} // namespace nxc