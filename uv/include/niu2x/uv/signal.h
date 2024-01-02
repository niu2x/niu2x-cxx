#ifndef NIU2X_UV_SIGNAL_H
#define NIU2X_UV_SIGNAL_H

#include <niu2x/noncopyable.h>
#include <niu2x/malloc_handle.h>
#include <niu2x/uv/exception.h>

namespace niu2x::uv {

class Loop;

class Signal : private Noncopyable {
public:
    using SignalCallback = Function<void(int signum)>;
    Signal(Loop* loop, SignalCallback callback);
    ~Signal();
    void* native() const { return native_.data(); }
    void start(int signum);
    void stop();

private:
    MallocHandle native_;
    SignalCallback callback_;
    Loop* loop_;
    static void uv_callback(void*, int signum);
};

} // namespace niu2x::uv

#endif