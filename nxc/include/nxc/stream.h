#ifndef NXC_STREAM_H
#define NXC_STREAM_H

#include <nxc/api.h>
#include <nxc/result.h>

namespace nxc {

template <class Ch, int BUF_SIZE>
class ReadStream {
public:
    using Char = Ch;

    ReadStream() { reset(); }

    virtual ~ReadStream() { }

    Result<Char> read()
    {
        if (should_pull()) {
            auto ret = pull();
            if (!ret)
                return ret;
        }
        return *(next_++);
    }

    void reset() { next_ = end_ = buf_; }

protected:
    virtual Result<size_t> _pull(Char* ptr, size_t count) = 0;

private:
    Char buf_[BUF_SIZE];
    Char* next_;
    Char* end_;

    bool should_pull() { return next_ >= end_; }

    // prefix condition: should_pull() == true
    Result<size_t> pull()
    {
        auto ret = _pull(buf_, BUF_SIZE);
        if (ret) {
            next_ = buf_;
            end_ = buf_ + *ret;
        }
        return ret;
    }
};

template <class Ch, int BUF_SIZE>
class WriteStream {
public:
    using Char = Ch;

    WriteStream() { reset(); }

    virtual ~WriteStream() { }

    Result<void> write(Ch c)
    {
        if (should_flush()) {
            auto ret = flush();
            if (!ret)
                return ret;
        }
        *(next_++) = c;
        return E::OK;
    }

    void reset() { next_ = begin_ = buf_; }

    Result<size_t> flush()
    {
        auto ret = _flush(begin_, next_ - begin_);
        if (ret) {
            begin_ += *ret;
            if (next_ - begin_ > 0) {
                auto count = next_ - begin_;
                memmove(buf_, begin_, (next_ - begin_) * sizeof(Char));
                begin_ = buf_;
                next_ = count + buf_;
            } else {
                next_ = begin_ = buf_;
            }
        }
        return ret;
    }

protected:
    virtual Result<size_t> _flush(Char* ptr, size_t count) = 0;

private:
    Char buf_[BUF_SIZE];
    Char* next_;
    Char* begin_;

    bool should_flush() { return next_ >= buf_ + BUF_SIZE; }
};

class NXC_API FileReadStream : public ReadStream<uint8_t, 1024> {
public:
    FileReadStream();
    virtual ~FileReadStream();

    Result<void> open(const String& path);
    void close();

protected:
    virtual Result<size_t> _pull(Char* buf, size_t count) override;

private:
    FILE* fp_;
};

} // namespace nxc

#endif