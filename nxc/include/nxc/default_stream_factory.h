#ifndef NXC_DEFAULT_STREAM_FACTORY_H
#define NXC_DEFAULT_STREAM_FACTORY_H

#include <nxc/stream_factory.h>

namespace nxc {

class NXC_API DefaultStreamFactory : public StreamFactory {
public:
    DefaultStreamFactory() { }
    virtual ~DefaultStreamFactory() { }

    virtual ReadStreamPtr create_read_stream(
        FilePtr file, bool auto_close_file) override;
    virtual WriteStreamPtr create_write_stream(
        FilePtr file, bool auto_close_file) override;

    virtual ReadStreamPtr create_read_stream(const Buffer* buffer) override;
    virtual WriteStreamPtr create_write_stream(Buffer* buffer) override;
};

} // namespace nxc

#endif