#ifndef NXC_STREAM_FACTORY_H
#define NXC_STREAM_FACTORY_H

#include <nxc/stream.h>
#include <nxc/buffer.h>

namespace nxc {

class NXC_API StreamFactory : public Singleton<StreamFactory> {
public:
    StreamFactory() { }
    ~StreamFactory() { }

    Result<ReadStreamPtr> create_read_stream(const String& pathname);
    Result<WriteStreamPtr> create_write_stream(const String& pathname);

    Result<ReadStreamPtr> create_read_stream(const Buffer* buffer);
    Result<WriteStreamPtr> create_write_stream(Buffer* buffer);
};

using StreamFactoryPtr = Ptr<StreamFactory>;

} // namespace nxc

#endif