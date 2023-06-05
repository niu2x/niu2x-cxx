#ifndef NXC_RESULT_H
#define NXC_RESULT_H

#include <nxc/api.h>
#include <nxc/error.h>
#include <nxc/utils.h>

namespace nxc {

// user need handle error, even if no programming error
template <class T>
// value
class Result {
public:
    Result()
    : Result(E::OK)
    {
    }

    Result(T&& t)
    : data_(std::forward<T>(t))
    , error_(E::OK)
    {
    }

    Result(const Error& e)
    : error_(e)
    {
    }

    Result(const Error& e, const String& msg)
    : error_(e)
    , msg_(msg)
    {
    }

    Result(const Error& e, String&& msg)
    : error_(e)
    , msg_(std::move(msg))
    {
    }

    NXC_COPYABLE_DEFAULT(Result)
    NXC_MOVABLE_DEFAULT(Result)

    template <class U>
    Result(const Result<U>& other)
    {
        NXC_ASSERT(!other, "not allowed");
        error_ = other.error();
        msg_ = other.error_msg();
    }

    ~Result() { }

    operator bool() const { return error_ == E::OK; }

    const Error& error() const { return error_; }
    const std::string& error_msg() const { return msg_; }

    const T& operator*() const { return data_; }
    T& operator*() { return data_; }

    const T& get() const { return data_; }
    T& get() { return data_; }

private:
    T data_;
    Error error_;
    String msg_;
};

template <>
class NXC_API Result<void> {
public:
    Result()
    : Result(E::OK)
    {
    }

    Result(const Error& e)
    : error_(e)
    {
    }

    Result(const Error& e, const String& msg)
    : error_(e)
    , msg_(msg)
    {
    }

    Result(const Error& e, String&& msg)
    : error_(e)
    , msg_(std::move(msg))
    {
    }

    NXC_COPYABLE_DEFAULT(Result)
    NXC_MOVABLE_DEFAULT(Result)

    template <class U>
    Result(const Result<U>& other)
    {
        NXC_ASSERT(!other, "not allowed");
        error_ = other.error();
        msg_ = other.error_msg();
    }

    ~Result() { }

    operator bool() const { return error_ == E::OK; }

    const Error& error() const { return error_; }
    const std::string& error_msg() const { return msg_; }

private:
    Error error_;
    String msg_;
};

} // namespace nxc

#endif