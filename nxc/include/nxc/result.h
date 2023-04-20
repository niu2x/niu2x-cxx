#ifndef NXC_RESULT_H
#define NXC_RESULT_H

#include <nxc/api.h>
#include <nxc/error.h>
#include <nxc/utils.h>

namespace nxc {

// user need handle error, even if no program error
template <class T>
class Result {
public:
    Result()
    : Result(E::OK)
    {
    }

    Result(const T& t)
    : data_(t)
    , error_(E::OK)
    {
    }

    Result(const Error& e)
    : error_(e)
    {
    }

    NXC_COPYABLE_DEFAULT(Result)

    template <class U>
    Result(const Result<U>& other)
    {
        NXC_ASSERT(!other, "not allowed");
        error_ = other.error();
    }

    ~Result() { }

    operator bool() const { return error_ == E::OK; }

    const Error& error() const { return error_; }

    const T& operator*() const { return data_; }
    T& operator*() { return data_; }

private:
    T data_;
    Error error_;
};

template <>
class NXC_API Result<void> {
public:
    Result()
    : error_(E::OK)
    {
    }

    Result(const Error& e)
    : error_(e)
    {
    }

    NXC_COPYABLE_DEFAULT(Result)

    template <class U>
    Result(const Result<U>& other)
    {
        NXC_ASSERT(!other, "not allowed");
        error_ = other.error();
    }

    ~Result() { }

    operator bool() const { return error_ == E::OK; }
    const Error& error() const { return error_; }

private:
    Error error_;
};

} // namespace nxc

#endif