#ifndef NXC_DATA_STREAM_H
#define NXC_DATA_STREAM_H

#include <nxc/utils.h>
#include <nxc/stream.h>
#include <nxc/data.h>

namespace nxc {

class DataReadStream : public ReadStream {
public:
    DataReadStream(const Data& data);
    virtual ~DataReadStream();

protected:
    virtual Result<size_t> _read(void* buf, size_t n) override;

private:
    const Data& data_;
    size_t pos_;
};

class DataWriteStream : public WriteStream {
public:
    DataWriteStream(Data& data);
    virtual ~DataWriteStream();

protected:
    virtual Result<size_t> _write(const void* buf, size_t n) override;

private:
    Data& data_;
    size_t pos_;
};

} // namespace nxc

#endif