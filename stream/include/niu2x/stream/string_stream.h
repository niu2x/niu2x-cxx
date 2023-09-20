#ifndef NIU2X_STREAM_FILE_STREAM_H
#define NIU2X_STREAM_FILE_STREAM_H

#include <niu2x/stream/stream.h>

namespace niu2x::stream {

class NXAPI StringReadStream : public ReadStream {
public:
    StringReadStream(const fs::File& file);
    virtual ~StringReadStream();
    virtual size_t read(void* buf, size_t size) override;
    virtual bool eof() override;

private:
    String sz_;
};

class NXAPI StringWriteStream : public WriteStream {
public:
    StringWriteStream(const fs::File& file);
    virtual ~StringWriteStream();
    virtual void write(const void* buf, size_t size) override;
    const String& str() const;

private:
    StringBuf sb_;
};

} // namespace niu2x::stream

#endif