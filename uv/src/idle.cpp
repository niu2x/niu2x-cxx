#include "uv.h"
#include "helper.h"
#include <niu2x/uv/idle.h>
#include <niu2x/uv/loop.h>
#include <niu2x/unused.h>

namespace niu2x::uv2 {

Idle::Idle(Loop* loop, IdleCallback callback)
: native_(sizeof(uv_idle_t))
, callback_(callback)
, loop_(loop)
{
    auto uv_idle = UV_TYPE(uv_idle_t*, native_.data());
    memset(uv_idle, 0, sizeof(uv_idle_t));

    auto uv_loop = reinterpret_cast<uv_loop_t*>(loop->native());
    uv_idle_init(uv_loop, uv_idle);
    uv_idle->data = this;
}

Idle::~Idle()
{
    auto uv_idle = UV_TYPE(uv_idle_t*, native_.data());
    UV_ENSURE_STOP(uv_idle, uv_idle_stop);
    UV_ENSURE_CLOSE(uv_idle, loop_);
}

void Idle::uv_callback(void* p_idle)
{
    auto uv_idle = UV_TYPE(uv_idle_t*, p_idle);
    auto idle = reinterpret_cast<Idle*>(uv_idle->data);
    idle->callback_();
}

void Idle::start()
{
    using CALLBACK_T = void (*)(uv_idle_s*);
    auto uv_idle = UV_TYPE(uv_idle_t*, native_.data());
    uv_idle_start(uv_idle, (CALLBACK_T)Idle::uv_callback);
}

void Idle::stop()
{
    auto uv_idle = UV_TYPE(uv_idle_t*, native_.data());
    uv_idle_stop(uv_idle);
}

}; // namespace niu2x::uv2