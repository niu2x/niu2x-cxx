#ifndef NIU2X_UV_IDLE_H
#define NIU2X_UV_IDLE_H

#include <niu2x/noncopyable.h>
#include <niu2x/uv/exception.h>
#include <niu2x/malloc_handle.h>

namespace niu2x::uv {

class Loop;

class Idle : private Noncopyable {
public:
    using IdleCallback = Function<void()>;

    Idle(Loop* loop, IdleCallback callback);
    ~Idle();

    void* native() const { return native_.data(); }
    void start();
    void stop();

private:
    MallocHandle native_;
    IdleCallback callback_;
    Loop* loop_;
    static void uv_callback(void*);
};

} // namespace niu2x::uv

#endif