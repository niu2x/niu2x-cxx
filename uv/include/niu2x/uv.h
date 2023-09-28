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

private:
    UniquePtr<LoopImp> pimp_;
};

} // namespace niu2x::uv

#endif
