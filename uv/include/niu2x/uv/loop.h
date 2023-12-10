#ifndef NIU2X_UV_LOOP_H
#define NIU2X_UV_LOOP_H

#include <niu2x/noncopyable.h>
#include <niu2x/type.h>
#include <niu2x/uv/exception.h>

namespace niu2x::uv2 {

class Loop : private Noncopyable {
public:
    Loop();
    ~Loop();
    void run();
    void* native() const { return native_.data(); }

private:
    MallocHandle native_;
};

} // namespace niu2x::uv2

#endif