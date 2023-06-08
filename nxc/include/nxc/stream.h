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
        if (full()) {
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
                memmove(buf_, begin_, count * sizeof(Char));
                begin_ = buf_;
                next_ = count + buf_;
            } else {
                next_ = begin_ = buf_;
            }
        }
        return ret;
    }

    void flush_all()
    {
        while (!empty()) {
            auto ret = flush();
            if (!ret && ret.error() != E ::WAIT_IO)
                break;
        }
    }

protected:
    virtual Result<size_t> _flush(Char* ptr, size_t count) = 0;

private:
    Char buf_[BUF_SIZE];
    Char* next_;
    Char* begin_;

    bool full() const { return next_ >= buf_ + BUF_SIZE; }
    bool empty() const { return next_ == begin_; }
};

} // namespace nxc

#endif