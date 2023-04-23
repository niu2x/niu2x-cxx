#ifndef NXC_STREAM_FACTORY_H
#define NXC_STREAM_FACTORY_H

#include <nxc/stream.h>
#include <nxc/buffer.h>
#include <nxc/file.h>
#include <nxc/file_factory.h>

namespace nxc {

class NXC_API StreamFactory {
public:
    StreamFactory() { }
    virtual ~StreamFactory() { }

    void set_file_factory(FileFactoryPtr);

    virtual ReadStreamPtr create_read_stream(File* file) = 0;
    virtual WriteStreamPtr create_write_stream(File* file) = 0;

    virtual ReadStreamPtr create_read_stream(FilePtr file) = 0;
    virtual WriteStreamPtr create_write_stream(FilePtr file) = 0;

    ReadStreamPtr create_read_stream(const String& pathname);
    WriteStreamPtr create_write_stream(const String& pathname);

    virtual ReadStreamPtr create_read_stream(const Buffer* buffer) = 0;
    virtual WriteStreamPtr create_write_stream(Buffer* buffer) = 0;

private:
    FileFactoryPtr file_factory_;
};

using StreamFactoryPtr = Ptr<StreamFactory>;

} // namespace nxc

#endif