#include <nxc/stream_factory.h>
#include <nxc/file_factory.h>
#include "file_stream.h"
#include "buffer_stream.h"

namespace nxc {

ReadStreamPtr StreamFactory::create_read_stream(const String& pathname)
{
    auto file = FileFactory::get()->create(pathname);
    if (file && file->open(OpenMode::READ)) {
        auto s = create_read_stream(file, true);
        return s;
    }
    return nullptr;
}

WriteStreamPtr StreamFactory::create_write_stream(const String& pathname)
{
    auto file = FileFactory::get()->create(pathname);
    if (file && file->open(OpenMode::WRITE)) {
        auto s = create_write_stream(file, true);
        return s;
    }
    return nullptr;
}

ReadStreamPtr StreamFactory::create_read_stream(
    FilePtr file, bool auto_close_file)
{
    return NXC_MAKE_PTR(FileReadStream, file, auto_close_file);
}
WriteStreamPtr StreamFactory::create_write_stream(
    FilePtr file, bool auto_close_file)
{
    return NXC_MAKE_PTR(FileWriteStream, file, auto_close_file);
}

ReadStreamPtr StreamFactory::create_read_stream(const Buffer* buffer)
{
    NXC_ASSERT(buffer != nullptr, "buffer is nullptr");
    return NXC_MAKE_PTR(BufferReadStream, buffer);
}
WriteStreamPtr StreamFactory::create_write_stream(Buffer* buffer)
{
    NXC_ASSERT(buffer != nullptr, "buffer is nullptr");
    return NXC_MAKE_PTR(BufferWriteStream, buffer);
}

StreamFactory* StreamFactory::get()
{
    static StreamFactory instance;
    return &instance;
}

} // namespace nxc