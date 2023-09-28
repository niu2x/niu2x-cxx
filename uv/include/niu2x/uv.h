#ifndef NIU2X_UV_H
#define NIU2X_UV_H

#include <niu2x/noncopyable.h>
#include <niu2x/type.h>
#include <niu2x/uv/exception.h>

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

private:
    UniquePtr<LoopImp> pimp_;

    LoopImp* imp() { return pimp_.get(); }
};

} // namespace niu2x::uv

#endif
