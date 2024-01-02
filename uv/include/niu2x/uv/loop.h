#ifndef NIU2X_UV_LOOP_H
#define NIU2X_UV_LOOP_H

#include <niu2x/noncopyable.h>
#include <niu2x/malloc_handle.h>
#include <niu2x/std_alias.h>
#include <niu2x/uv/exception.h>

namespace niu2x::uv {

class Loop : private Noncopyable {
public:
    Loop();
    ~Loop();

    void run_loop();
    void run_once();

    void* native() const { return native_.data(); }

    NIU2X_PP_MOVABLE(Loop);

private:
    MallocHandle native_;
};

static_assert(type_pred::is_movable<Loop>);

} // namespace niu2x::uv

#endif