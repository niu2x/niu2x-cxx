#ifndef NIU2X_UV_H
#define NIU2X_UV_H

#include <niu2x/noncopyable.h>
#include <niu2x/type.h>
#include <niu2x/uv/exception.h>
#include <niu2x/uv/loop.h>
#include <niu2x/uv/idle.h>
#include <niu2x/uv/timer.h>
#include <niu2x/uv/signal.h>

namespace niu2x::uv {

class LoopImp;

class Loop : private Noncopyable {
public:
    Loop();
    ~Loop();
    void close();
    void run();

    using IdleCallback = Function<void()>;

    void* create_idle();
    void destroy_idle(void*);

    void idle_start(void*, const IdleCallback& idle_cb);
    void idle_stop(void*);

    using TimerCallback = Function<void()>;

    void* create_timer();
    void destroy_timer(void*);

    void timer_start(void*, uint64_t timeout, uint64_t repeat,
        const TimerCallback& timer_cb);
    void timer_stop(void*);

    using SignalCallback = Function<void(int signum)>;
    void* create_signal();
    void destroy_signal(void*);
    void signal_start(void*, int signum, const SignalCallback& timer_cb);
    void signal_stop(void*);

private:
    UniquePtr<LoopImp> pimp_;

    LoopImp* imp() { return pimp_.get(); }
};

} // namespace niu2x::uv

#endif
