#include <niu2x/uv.h>
#include "uv.h"

#define THROW_UV_ERR(n) throw_runtime_err(uv_strerror((n)));

#define CHECK_UV_ERR(expr_or_err)                                              \
    if (auto n = (expr_or_err) < 0) {                                          \
        THROW_UV_ERR(n);                                                       \
    }

#define CONTAINER_OF(ptr, st, member)                                          \
    ((st*)(((uint8_t*)(ptr)) - ((uint8_t*)(&(((st*)0)->member)) - (uint8_t*)0)))

namespace niu2x::uv {

class LoopImp : private Noncopyable {
public:
    struct Idle {
        uv_idle_t uv_idle;
        Loop::IdleCallback cb;
    };

    struct Timer {
        uv_timer_t uv_timer;
        Loop::TimerCallback cb;
    };

    struct Signal {
        uv_signal_t uv_signal;
        Loop::SignalCallback cb;
    };

    LoopImp()
    {
        loop_ = &self_loop_;
        CHECK_UV_ERR(uv_loop_init(loop_));
    }

    ~LoopImp() { }

    void run() { CHECK_UV_ERR(uv_run(loop_, UV_RUN_DEFAULT)); }

    void close()
    {
        auto err = uv_loop_close(loop_);
        if (err == UV_EBUSY)
            throw LoopBusy();

        CHECK_UV_ERR(err);
    }

    void* create_idle()
    {
        auto idle = (Idle*)malloc(sizeof(Idle));
        uv_idle_init(loop_, &(idle->uv_idle));
        idle->uv_idle.data = idle;
        return idle;
    }

    void destroy_idle(void* p_idle)
    {
        auto idle = reinterpret_cast<Idle*>(p_idle);
        auto handle = reinterpret_cast<uv_handle_t*>(&(idle->uv_idle));

        if (uv_is_active(handle)) {
            uv_idle_stop(&(idle->uv_idle));
        }

        if (!uv_is_closing(handle)) {
            uv_close(handle, uv_close_cb);
        }
    }

    void idle_start(void* p_idle, const Loop::IdleCallback& idle_cb)
    {
        auto idle = reinterpret_cast<Idle*>(p_idle);
        idle->cb = idle_cb;
        uv_idle_start(&(idle->uv_idle), uv_idle_cb);
    }

    void idle_stop(void* p_idle)
    {
        auto idle = reinterpret_cast<Idle*>(p_idle);
        uv_idle_stop(&(idle->uv_idle));
    }

    void* create_timer()
    {
        auto timer = (Timer*)malloc(sizeof(Timer));
        uv_timer_init(loop_, &(timer->uv_timer));
        timer->uv_timer.data = timer;
        return timer;
    }

    void destroy_timer(void* p_timer)
    {
        auto timer = reinterpret_cast<Timer*>(p_timer);
        auto handle = reinterpret_cast<uv_handle_t*>(&(timer->uv_timer));

        if (uv_is_active(handle)) {
            uv_timer_stop(&(timer->uv_timer));
        }

        if (!uv_is_closing(handle)) {
            uv_close(handle, uv_close_cb);
        }
    }

    void timer_start(void* p_timer, uint64_t timeout, uint64_t repeat,
        const Loop::TimerCallback& timer_cb)
    {
        auto timer = reinterpret_cast<Timer*>(p_timer);
        timer->cb = timer_cb;
        uv_timer_start(&(timer->uv_timer), uv_timer_cb, timeout, repeat);
    }

    void timer_stop(void* p_timer)
    {
        auto timer = reinterpret_cast<Timer*>(p_timer);
        uv_timer_stop(&(timer->uv_timer));
    }

    void* create_signal()
    {
        auto signal = (Signal*)malloc(sizeof(Signal));
        uv_signal_init(loop_, &(signal->uv_signal));
        signal->uv_signal.data = signal;
        return signal;
    }
    void destroy_signal(void* p_signal)
    {
        auto signal = reinterpret_cast<Signal*>(p_signal);
        auto handle = reinterpret_cast<uv_handle_t*>(&(signal->uv_signal));

        if (uv_is_active(handle)) {
            uv_signal_stop(&(signal->uv_signal));
        }

        if (!uv_is_closing(handle)) {
            uv_close(handle, uv_close_cb);
        }
    }
    void signal_start(
        void* p_signal, int signum, const Loop::SignalCallback& signal_cb)
    {
        auto signal = reinterpret_cast<Signal*>(p_signal);
        signal->cb = signal_cb;
        uv_signal_start(&(signal->uv_signal), uv_signal_cb, signum);
    }
    void signal_stop(void* p_signal)
    {
        auto signal = reinterpret_cast<Signal*>(p_signal);
        uv_signal_stop(&(signal->uv_signal));
    }

private:
    uv_loop_t self_loop_;
    uv_loop_t* loop_;

    uv_loop_t* uv_loop() { return loop_; }

    static void uv_close_cb(uv_handle_t* handle) { free(handle); }
    static void uv_idle_cb(uv_idle_t* p_idle)
    {
        auto idle = CONTAINER_OF(p_idle, Idle, uv_idle);
        idle->cb();
    }

    static void uv_timer_cb(uv_timer_t* p_timer)
    {
        auto timer = CONTAINER_OF(p_timer, Timer, uv_timer);
        timer->cb();
    }
    static void uv_signal_cb(uv_signal_t* p_signal, int signum)
    {
        auto signal = CONTAINER_OF(p_signal, Signal, uv_signal);
        signal->cb(signum);
    }
};

Loop::Loop()
: pimp_(make_unique<LoopImp>())
{
}

Loop::~Loop() { }

void Loop::run() { pimp_->run(); }

void Loop::close() { pimp_->close(); }

void* Loop::create_idle() { return pimp_->create_idle(); }

void Loop::destroy_idle(void* idle) { pimp_->destroy_idle(idle); }

void Loop::idle_start(void* idle, const IdleCallback& idle_cb)
{
    pimp_->idle_start(idle, idle_cb);
}

void Loop::idle_stop(void* idle) { pimp_->idle_stop(idle); }

void* Loop::create_timer() { return pimp_->create_timer(); }

void Loop::destroy_timer(void* timer) { pimp_->destroy_timer(timer); }

void Loop::timer_start(void* timer, uint64_t timeout, uint64_t repeat,
    const TimerCallback& timer_cb)
{
    pimp_->timer_start(timer, timeout, repeat, timer_cb);
}
void Loop::timer_stop(void* timer) { pimp_->timer_stop(timer); }

void* Loop::create_signal() { return pimp_->create_signal(); }

void Loop::destroy_signal(void* signal) { pimp_->destroy_signal(signal); }

void Loop::signal_start(
    void* signal, int signum, const SignalCallback& signal_cb)
{
    pimp_->signal_start(signal, signum, signal_cb);
}
void Loop::signal_stop(void* signal) { pimp_->signal_stop(signal); }

} // namespace niu2x::uv