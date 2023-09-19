#ifndef NIU2X_STREAM_FILE_STREAM_H
#define NIU2X_STREAM_FILE_STREAM_H

#include <niu2x/stream/base_stream.h>
#include <niu2x/fs/file.h>

namespace niu2x::stream {

class NXAPI FileReadStream : public BaseReadStream {
public:
    FileReadStream(File* file);
    virtual ~FileReadStream();
    virtual size_t read(void* buf, size_t size) override;
    virtual bool eof() override;
};

class NXAPI FileWriteStream : public BaseWriteStream {
public:
    FileWriteStream(File* file);
    virtual ~FileWriteStream();
    virtual void write(const void* buf, size_t size) override;
};

} // namespace niu2x::stream

#endif