#ifndef NIU2X_UV_TIMER_H
#define NIU2X_UV_TIMER_H

#include <niu2x/noncopyable.h>
#include <niu2x/type.h>
#include <niu2x/uv/exception.h>

namespace niu2x::uv {

class Loop;

class Timer : private Noncopyable {
public:
    using TimerCallback = Function<void()>;
    Timer(Loop* loop, TimerCallback callback, TimeDuration interval);
    ~Timer();
    void* native() const { return native_.data(); }
    void start();
    void stop();

private:
    MallocHandle native_;
    TimerCallback callback_;
    Loop* loop_;
    int64_t interval_;
    static void uv_callback(void*);
};

} // namespace niu2x::uv

#endif