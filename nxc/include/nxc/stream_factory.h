#ifndef NXC_STREAM_FACTORY_H
#define NXC_STREAM_FACTORY_H

#include <nxc/stream.h>
#include <nxc/buffer.h>
#include <nxc/file.h>

namespace nxc {

class NXC_API StreamFactory {
public:
    static StreamFactory* get();

    StreamFactory() { }
    ~StreamFactory() { }

    ReadStreamPtr create_read_stream(FilePtr file, bool auto_close_file);
    WriteStreamPtr create_write_stream(FilePtr file, bool auto_close_file);

    ReadStreamPtr create_read_stream(const String& pathname);
    WriteStreamPtr create_write_stream(const String& pathname);

    ReadStreamPtr create_read_stream(const Buffer* buffer);
    WriteStreamPtr create_write_stream(Buffer* buffer);
};

using StreamFactoryPtr = Ptr<StreamFactory>;

} // namespace nxc

#endif