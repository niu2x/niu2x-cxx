#include <nxc/stream_factory.h>
#include "file_factory.h"
#include "file_stream.h"
#include "data_stream.h"
#include "buffer_stream.h"
#include "file2stream.h"

namespace nxc {

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

Result<ReadStreamPtr> StreamFactory::create_read_stream(const Data& data)
{
    return (ReadStreamPtr)NXC_MAKE_PTR(DataReadStream, data);
}
Result<WriteStreamPtr> StreamFactory::create_write_stream(Buffer& buffer)
{
    return (WriteStreamPtr)NXC_MAKE_PTR(BufferWriteStream, buffer);
}

} // namespace nxc