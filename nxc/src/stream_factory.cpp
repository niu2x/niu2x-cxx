#include <nxc/stream_factory.h>
#include "file_factory.h"
#include "file_stream.h"
#include "buffer_stream.h"

namespace nxc {

static ReadStreamPtr create_read_stream(FilePtr file, bool auto_close_file)
{
    return NXC_MAKE_PTR(FileReadStream, file, auto_close_file);
}

static WriteStreamPtr create_write_stream(FilePtr file, bool auto_close_file)
{
    return NXC_MAKE_PTR(FileWriteStream, file, auto_close_file);
}

Result<ReadStreamPtr> StreamFactory::create_read_stream(const String& pathname)
{
    auto file = FileFactory::get()->create(pathname);
    auto open_result = file->open(OpenMode::READ);
    if (open_result) {
        return nxc::create_read_stream(file, true);
    }
    return open_result;
}

Result<WriteStreamPtr> StreamFactory::create_write_stream(
    const String& pathname)
{
    auto file = FileFactory::get()->create(pathname);
    auto open_result = file->open(OpenMode::WRITE);
    if (open_result) {
        return nxc::create_write_stream(file, true);
    }
    return open_result;
}

Result<ReadStreamPtr> StreamFactory::create_read_stream(const Buffer* buffer)
{
    NXC_ASSERT(buffer != nullptr, "buffer is nullptr");
    return (ReadStreamPtr)NXC_MAKE_PTR(BufferReadStream, buffer);
}
Result<WriteStreamPtr> StreamFactory::create_write_stream(Buffer* buffer)
{
    NXC_ASSERT(buffer != nullptr, "buffer is nullptr");
    return (WriteStreamPtr)NXC_MAKE_PTR(BufferWriteStream, buffer);
}

} // namespace nxc