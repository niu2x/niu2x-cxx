#include "archive_zip.h"
#include "file_helper.h"

namespace nxc {

class EntryFile : public File {
public:
    EntryFile(const String& path, zip_t* zip, OpenMode zip_mode,
        ArchiveZip::BufferPtrVector& buffers)
    : pathname_(path)
    , zip_(zip)
    , file_(nullptr)
    , closed_(true)
    , zip_mode_(zip_mode)
    , zip_buffers_(buffers)
    {
    }
    virtual ~EntryFile() { close(); }

protected:
    // virtual bool _eof() const override { return false; }
    virtual Result<void> _seek(SeekPos relative, size_t offset) override
    {
        NXC_ASSERT(file_, "fp_ is nullptr");
        auto flag = seek_flag(relative);
        auto ret = zip_fseek(file_, offset, flag);
        if (ret < 0)
            return E::ZIP_LIB_ERROR;
        return E::OK;
    }
    virtual Result<size_t> _tell() const override
    {
        NXC_ASSERT(file_ != nullptr, "file_ is nullptr")
        auto pos = zip_ftell(file_);
        if (pos < 0)
            return E::ZIP_LIB_ERROR;
        return static_cast<size_t>(pos);
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
        buffer_->write(buf, n);
        return n;
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
        buffer_ = NXC_MAKE_PTR(Buffer);
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
        if (mode_ == OpenMode::WRITE) {
            struct zip_source* s
                = zip_source_buffer(zip_, buffer_->data(), buffer_->size(), 0);

            NXC_ASSERT(s != nullptr, "s is nullptr");
            if (zip_file_add(zip_, pathname_.c_str(), s,
                    ZIP_FL_ENC_UTF_8 | ZIP_FL_OVERWRITE)
                < 0) {
                zip_source_free(s);
                NXC_ASSERT(false, "zip add file failed");
            }

            zip_buffers_.push_back(buffer_);

            buffer_ = nullptr;
        }
    }

private:
    String pathname_;
    zip_t* zip_;
    OpenMode mode_;
    zip_file_t* file_;
    BufferPtr buffer_;
    bool closed_;
    OpenMode zip_mode_;
    ArchiveZip::BufferPtrVector& zip_buffers_;
};

static int figure_flags(OpenMode mode)
{
    if (mode == OpenMode::READ)
        return ZIP_RDONLY;
    if (mode == OpenMode::WRITE)
        return ZIP_CREATE | ZIP_TRUNCATE;
    return ZIP_CREATE;
}

ArchiveZip::ArchiveZip(const String& p)
: pathname_(p)
, zip_(nullptr)
{
}

ArchiveZip::~ArchiveZip() { close(); }

Result<void> ArchiveZip::_open(OpenMode mode)
{
    NXC_ASSERT(!zip_, "zip_ is not nullptr");
    mode_ = mode;
    int flags = figure_flags(mode_);
    zip_ = zip_open(pathname_.c_str(), flags, nullptr);
    return zip_ ? E::OK : E::ZIP_LIB_ERROR;
}

void ArchiveZip::_close()
{
    if (zip_) {
        NXC_ASSERT(opened_files_.size() == 0, "there are opend files.");
        zip_close(zip_);
        zip_ = nullptr;
    }
}

FilePtr ArchiveZip::_open_entry(const String& entry)
{
    NXC_ASSERT(zip_, "zip_ is nullptr");
    auto file = NXC_MAKE_PTR(EntryFile, entry, zip_, mode_, write_buffers_);
    opened_files_.push_back(file);
    return file;
}
bool ArchiveZip::_exist_entry(const String& entry) const
{
    NXC_ASSERT(zip_, "zip_ is nullptr");
    return zip_name_locate(zip_, entry.c_str(), ZIP_FL_ENC_UTF_8) != -1;
}

void ArchiveZip::_close_entry(FilePtr file)
{
    if (file) {
        auto it = opened_files_.walk();
        while (it.has_value()) {
            if (it.get() == file) {
                opened_files_.erase(it);
                break;
            }
            it.next();
        }
    }
}

} // namespace nxc
