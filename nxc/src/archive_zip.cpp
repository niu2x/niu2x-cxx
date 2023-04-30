#include "archive_zip.h"
#include "file_helper.h"
#include "file2stream.h"

namespace nxc {

class EntryFile : public File {
public:
    EntryFile(const String& path, zip_t* zip, OpenMode zip_mode, int& counter)
    : pathname_(path)
    , zip_(zip)
    , file_(nullptr)
    , closed_(true)
    , zip_mode_(zip_mode)
    , counter_(counter)
    {
        counter_++;
    }
    virtual ~EntryFile()
    {
        NXC_ASSERT(file_ == nullptr, "file is not closed");
        counter_--;
    }

protected:
    // virtual bool _eof() const override { return false; }
    virtual Result<void> _seek(SeekPos relative, long offset) override
    {
        NXC_ASSERT(file_, "fp_ is nullptr");
        auto flag = seek_flag(relative);
        auto ret = zip_fseek(file_, offset, flag);
        if (ret < 0)
            return E::ZIP_LIB_ERROR;
        return E::OK;
    }
    virtual Result<long> _tell() const override
    {
        NXC_ASSERT(file_ != nullptr, "file_ is nullptr")
        auto pos = zip_ftell(file_);
        if (pos < 0)
            return E::ZIP_LIB_ERROR;
        return pos;
    }

    virtual Result<size_t> _read(void* buf, size_t n) override
    {
        NXC_ASSERT(file_ != nullptr, "file_ is nullptr")
        auto ret = zip_fread(file_, buf, n);
        if (ret < 0)
            return E::ZIP_LIB_ERROR;
        if (ret == 0)
            return E::END_OF_FILE;
        return ret;
    }

    virtual Result<size_t> _write(const void* buf, size_t n) override
    {
        unused(buf);
        unused(n);
        return E::TODO;
    }

    virtual Result<void> _open(OpenMode mode) override
    {
        NXC_ASSERT(file_ == nullptr, "file_ is not nullptr")
        mode_ = mode;
        closed_ = false;
        if (mode_ == OpenMode::READ) {
            NXC_ASSERT(zip_mode_ == OpenMode::READ, "zip can not read");
            file_ = zip_fopen(zip_, pathname_.c_str(), ZIP_FL_ENC_UTF_8);
            return file_ != nullptr ? E::OK : E::ZIP_LIB_ERROR;
        }
        NXC_ASSERT(zip_mode_ == OpenMode::WRITE, "zip can not write");
        return E::OK;
    }

    virtual void _close() override
    {
        if (closed_)
            return;
        closed_ = true;

        if (mode_ == OpenMode::READ) {
            if (file_) {
                zip_fclose(file_);
                file_ = nullptr;
            }
        }
    }

private:
    String pathname_;
    zip_t* zip_;
    OpenMode mode_;
    zip_file_t* file_;
    // BufferPtr buffer_;
    bool closed_;
    OpenMode zip_mode_;
    int& counter_;
};

static int figure_flags(OpenMode mode)
{
    switch (mode) {
        case OpenMode::READ:
            return ZIP_RDONLY;
        case OpenMode::WRITE:
            return ZIP_CREATE;
        default:
            return ZIP_RDONLY;
    }
}

ArchiveZip::ArchiveZip(const String& p)
: pathname_(p)
, zip_(nullptr)
, read_streams_(0)
, source_(nullptr)
{
}

ArchiveZip::ArchiveZip(const Data* data)
: pathname_("")
, zip_(nullptr)
, read_streams_(0)
, source_(data)
{
}

ArchiveZip::~ArchiveZip() { close(); }

Result<void> ArchiveZip::_open(OpenMode mode)
{
    NXC_ASSERT(!zip_, "zip_ is not nullptr");
    mode_ = mode;
    int flags = figure_flags(mode_);
    if (use_pathname()) {
        zip_ = zip_open(pathname_.c_str(), flags, nullptr);
    } else {
        zip_error_t error;
        zip_source_t* sb = zip_source_buffer_create(
            source_->data(), source_->size(), 0, &error);
        if (!sb) {
            return E::ZIP_LIB_ERROR;
        }
        zip_ = zip_open_from_source(sb, flags, &error);
        if (!zip_) {
            zip_source_free(sb);
        }
    }
    return zip_ ? E::OK : E::ZIP_LIB_ERROR;
}

void ArchiveZip::_close()
{
    if (zip_) {
        NXC_ASSERT(read_streams_ == 0, "there are opend files.");
        zip_close(zip_);
        zip_ = nullptr;
    }
}

Result<ReadStreamPtr> ArchiveZip::_read_entry(const String& entry)
{
    NXC_ASSERT(zip_, "zip_ is nullptr");

    if (!_exist_entry(entry)) {
        return E::NO_EXIST;
    }

    auto file = NXC_MAKE_PTR(EntryFile, entry, zip_, mode_, read_streams_);
    auto open_result = file->open(OpenMode::READ);
    if (open_result) {
        return create_read_stream(file, true);
    }
    return open_result;
}
bool ArchiveZip::_exist_entry(const String& entry) const
{
    NXC_ASSERT(zip_, "zip_ is nullptr");
    return zip_name_locate(zip_, entry.c_str(), ZIP_FL_ENC_UTF_8) != -1;
}

} // namespace nxc
