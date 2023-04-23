#ifndef NXC_FILE_STREAM_H
#define NXC_FILE_STREAM_H

#include <nxc/file.h>
#include <nxc/stream.h>

namespace nxc {

class FileReadStream : public ReadStream {
public:
    FileReadStream(FilePtr file);
    FileReadStream(File* file);
    virtual ~FileReadStream();
    void set_auto_close_file(bool b) { should_close_ = b; }

protected:
    virtual Result<size_t> _read(void* buf, size_t n) override;
    // virtual bool _eof() const override;

private:
    FilePtr file_;
    File* weak_file_;

    bool should_close_;
    void _close_file();
};

class FileWriteStream : public WriteStream {
public:
    FileWriteStream(FilePtr file);
    FileWriteStream(File* file);
    virtual ~FileWriteStream();
    void set_auto_close_file(bool b) { should_close_ = b; }

protected:
    virtual Result<size_t> _write(const void* buf, size_t n) override;

private:
    FilePtr file_;
    File* weak_file_;
    bool should_close_;

    void _close_file();
};

} // namespace nxc

#endif