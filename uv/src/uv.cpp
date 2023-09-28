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
        Loop* loop;
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
        idle->uv_idle.data = idle;
        uv_idle_init(loop_, &(idle->uv_idle));
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

} // namespace niu2x::uv