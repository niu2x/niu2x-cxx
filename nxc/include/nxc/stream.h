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
        Char c;
        auto ret = read(&c, 1);
        if (ret)
            return c;
        return ret;
    }

    void reset() { next_ = end_ = buf_; }

    Result<size_t> read(Char* buf, size_t count)
    {
        if (empty()) {
            auto ret = read_from_device();
            if (!ret)
                return ret;
        }

        size_t avai = end_ - next_;
        auto read_count = std::min(count, avai);
        memcpy(buf, next_, read_count * sizeof(Char));
        next_ += read_count;
        return read_count;
    }

    Result<void> readx(Char* buf, size_t count)
    {
        Result<size_t> ret = E::OK;
        do {
            ret = read(buf, count);
            if (ret) {
                count -= *ret;
                buf += *ret;
            } else {
                if (ret.error() != E::WAIT_IO)
                    break;
            }
        } while (count > 0);
        return ret;
    }

protected:
    virtual Result<size_t> _read_from_device(Char* ptr, size_t count) = 0;

private:
    Char buf_[BUF_SIZE];
    Char* next_;
    Char* end_;

    bool empty() { return next_ >= end_; }

    // prefix condition: empty() == true
    Result<size_t> read_from_device()
    {
        auto ret = _read_from_device(buf_, BUF_SIZE);
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
            auto ret = write_to_device();
            if (!ret)
                return ret;
        }
        *(next_++) = c;
        return E::OK;
    }

    void reset() { next_ = begin_ = buf_; }

    void flush()
    {
        while (!empty()) {
            auto ret = write_to_device();
            if (!ret && ret.error() != E ::WAIT_IO)
                break;
        }
    }

protected:
    virtual Result<size_t> _write_to_device(Char* ptr, size_t count) = 0;

private:
    Char buf_[BUF_SIZE];
    Char* next_;
    Char* begin_;

    bool full() const { return next_ >= buf_ + BUF_SIZE; }
    bool empty() const { return next_ == begin_; }

    Result<size_t> write_to_device()
    {
        auto ret = _write_to_device(begin_, next_ - begin_);
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
};

} // namespace nxc

#endif