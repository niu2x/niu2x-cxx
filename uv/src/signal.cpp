#include "uv.h"
#include "helper.h"
#include <niu2x/uv/signal.h>
#include <niu2x/uv/loop.h>
#include <niu2x/unused.h>
#include <string.h>

namespace niu2x::uv {

Signal::Signal(Loop* loop, SignalCallback callback)
: native_(sizeof(uv_signal_t))
, callback_(callback)
, loop_(loop)
{
    auto uv_signal = UV_TYPE(uv_signal_t*, native_.data());
    memset(uv_signal, 0, sizeof(uv_signal_t));

    auto uv_loop = UV_TYPE(uv_loop_t*, loop->native());
    uv_signal_init(uv_loop, uv_signal);
    uv_signal->data = this;
}

Signal::~Signal()
{
    auto uv_signal = UV_TYPE(uv_signal_t*, native_.data());
    UV_ENSURE_STOP(uv_signal, uv_signal_stop);
    UV_ENSURE_CLOSE(uv_signal, loop_);
}

void Signal::uv_callback(void* p_signal, int signum)
{
    UV_FETCH_WRAPPER(Signal, p_signal, signal);
    signal->callback_(signum);
}

void Signal::start(int signum)
{
    using CALLBACK_T = void (*)(uv_signal_s*, int);
    auto uv_signal = UV_TYPE(uv_signal_t*, native_.data());
    uv_signal_start(uv_signal, (CALLBACK_T)uv_callback, signum);
}

void Signal::stop()
{
    auto uv_signal = UV_TYPE(uv_signal_t*, native_.data());
    uv_signal_stop(uv_signal);
}

}; // namespace niu2x::uv