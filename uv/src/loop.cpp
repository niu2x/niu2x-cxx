#include <niu2x/uv/loop.h>
#include "uv.h"

#define THROW_UV_ERR(n) throw_runtime_err(uv_strerror((n)));

#define CHECK_UV_ERR(expr_or_err)                                              \
    if (auto n = (expr_or_err) < 0) {                                          \
        THROW_UV_ERR(n);                                                       \
    }

namespace niu2x::uv2 {

Loop::Loop()
: native_(sizeof(uv_loop_t))
{
    auto loop = reinterpret_cast<uv_loop_t*>(native_.data());
    memset(loop, 0, sizeof(uv_loop_t));
    CHECK_UV_ERR(uv_loop_init(loop));
}

void Loop::run_loop()
{
    auto loop = reinterpret_cast<uv_loop_t*>(native_.data());
    CHECK_UV_ERR(uv_run(loop, UV_RUN_DEFAULT));
}
void Loop::run_once()
{
    auto loop = reinterpret_cast<uv_loop_t*>(native_.data());
    CHECK_UV_ERR(uv_run(loop, UV_RUN_ONCE));
}

Loop::~Loop()
{
    auto loop = reinterpret_cast<uv_loop_t*>(native_.data());
    auto err = uv_loop_close(loop);
    if (err == UV_EBUSY)
        throw_runtime_err("uv loop busy");
    CHECK_UV_ERR(err);
}

} // namespace niu2x::uv2