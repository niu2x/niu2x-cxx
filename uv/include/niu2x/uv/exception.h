#ifndef NIU2X_UV_EXCEPTION_H
#define NIU2X_UV_EXCEPTION_H

#include <niu2x/type.h>

namespace niu2x::uv {

class LoopBusy : public RuntimeError {
public:
    LoopBusy()
    : RuntimeError("uv loop is busy")
    {
    }
};

} // namespace niu2x::uv

#endif
