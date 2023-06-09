#ifndef NXC_FILE_STREAM_H
#define NXC_FILE_STREAM_H

#include <nxc/stream.h>
#include <nxc/raii.h>

namespace nxc {

template <>
struct NXC_API Release<FILE*> {
    static void release(FILE* fp)
    {
        if (fp)
            fclose(fp);
    }
};

class NXC_API File : public RAII<FILE*> {
public:
    using Base = RAII<FILE*>;
    File(const String& path, OpenMode open_mode);
};

class NXC_API FileReadStream : public ReadStream<uint8_t, 1024> {
public:
    FileReadStream(const String& path);
    virtual ~FileReadStream();
    operator bool() const { return file_; }

protected:
    virtual Result<size_t> _read_from_device(Char* buf, size_t count) override;

private:
    File file_;
};

class NXC_API FileWriteStream : public WriteStream<uint8_t, 1024> {
public:
    FileWriteStream(const String& path);
    virtual ~FileWriteStream();
    operator bool() const { return file_; }

protected:
    virtual Result<size_t> _write_to_device(Char* ptr, size_t count) override;

private:
    File file_;
};

} // namespace nxc

#endif