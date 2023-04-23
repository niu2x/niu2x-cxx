#include <nxc/stream_factory.h>

namespace nxc {

ReadStreamPtr StreamFactory::create_read_stream(const String& pathname)
{
    NXC_ASSERT(file_factory_, "file_factory_ is nullptr");

    auto file = file_factory_->create(pathname);
    if (file && file->open(OpenMode::READ)) {
        auto s = create_read_stream(file);
        s->set_auto_close_file(true);
        return s;
    }
    return nullptr;
}

WriteStreamPtr StreamFactory::create_write_stream(const String& pathname)
{
    auto file = file_factory_->create(pathname);
    if (file && file->open(OpenMode::WRITE)) {
        auto s = create_write_stream(file);
        s->set_auto_close_file(true);
        return s;
    }
    return nullptr;
}

void StreamFactory::set_file_factory(FileFactoryPtr factory)
{
    file_factory_ = factory;
}

} // namespace nxc