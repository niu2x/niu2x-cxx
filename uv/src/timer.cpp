#include "uv.h"
#include "helper.h"
#include <niu2x/uv/timer.h>
#include <niu2x/uv/loop.h>
#include <niu2x/unused.h>

#define UV_TIMER()

namespace niu2x::uv2 {

Timer::Timer(Loop* loop, TimerCallback callback, uint64_t interval)
: native_(sizeof(uv_timer_t))
, callback_(callback)
, loop_(loop)
, interval_(interval)
{
    auto uv_timer = UV_TYPE(uv_timer_t*, native_.data());
    memset(uv_timer, 0, sizeof(uv_timer_t));

    auto uv_loop = UV_TYPE(uv_loop_t*, loop->native());
    uv_timer_init(uv_loop, uv_timer);
    uv_timer->data = this;
}

Timer::~Timer()
{
    auto uv_timer = UV_TYPE(uv_timer_t*, native_.data());
    UV_ENSURE_STOP(uv_timer, uv_timer_stop);
    UV_ENSURE_CLOSE(uv_timer, loop_);
}

void Timer::uv_callback(void* p_timer)
{
    auto uv_timer = reinterpret_cast<uv_timer_t*>(p_timer);
    auto timer = reinterpret_cast<Timer*>(uv_timer->data);
    timer->callback_();
}

void Timer::start()
{
    using CALLBACK_T = void (*)(uv_timer_s*);
    auto uv_timer = UV_TYPE(uv_timer_t*, native_.data());
    uv_timer_start(uv_timer, (CALLBACK_T)uv_callback, interval_, interval_);
}

void Timer::stop()
{
    auto uv_timer = UV_TYPE(uv_timer_t*, native_.data());
    uv_timer_stop(uv_timer);
}

}; // namespace niu2x::uv2