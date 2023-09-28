#include <niu2x/uv.h>
#include "uv.h"

#define THROW_UV_ERR(n) throw_runtime_err(uv_strerror((n)));

#define CHECK_UV_ERR(expr_or_err)                                              \
    if (auto n = (expr_or_err) < 0) {                                          \
        THROW_UV_ERR(n);                                                       \
    }

namespace niu2x::uv {

class LoopImp : private Noncopyable {
public:
    LoopImp()
    {
        loop_ = &self_loop_;
        CHECK_UV_ERR(uv_loop_init(loop_));
    }

    // LoopImp(uv_loop_t *external_loop) {
    // 	loop_ = external_loop;
    // 	setup();
    // }

    ~LoopImp() { }

    void close()
    {
        auto err = uv_loop_close(loop_);
        if (err == UV_EBUSY)
            throw LoopBusy();

        CHECK_UV_ERR(err);
    }

private:
    uv_loop_t self_loop_;
    uv_loop_t* loop_;
};

Loop::Loop()
: pimp_(make_unique<LoopImp>())
{
}

Loop::~Loop() { }

void Loop::close() { pimp_->close(); }

} // namespace niu2x::uv