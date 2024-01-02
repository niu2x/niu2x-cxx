#ifndef NIU2X_STREAM_FILE_STREAM_H
#define NIU2X_STREAM_FILE_STREAM_H

#include <niu2x/stream/file.h>
#include <niu2x/base_stream.h>
#include <niu2x/fs/file.h>

namespace niu2x::stream {

class FileReadStream : public ByteReadStream {
public:
    FileReadStream(const fs::File& file);
    virtual ~FileReadStream();
    virtual size_t read(uint8_t* buf, size_t size) override;
    virtual bool eof() override;

private:
    File file_;
};

class FileWriteStream : public ByteWriteStream {
public:
    FileWriteStream(const fs::File& file);
    virtual ~FileWriteStream();
    virtual void write(const uint8_t* buf, size_t size) override;

private:
    File file_;
};

} // namespace niu2x::stream

#endif