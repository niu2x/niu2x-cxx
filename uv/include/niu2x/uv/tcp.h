#ifndef NIU2X_UV_TCP_H
#define NIU2X_UV_TCP_H

#include <niu2x/noncopyable.h>
#include <niu2x/uv/exception.h>
#include <niu2x/malloc_handle.h>

namespace niu2x::uv {

class Loop;

class TCP : private Noncopyable {
public:
    TCP(Loop* loop);
    ~TCP();
    void* native() const { return native_.data(); }
    void bind(const String& ip, uint16_t port);

private:
    MallocHandle native_;
    Loop* loop_;
};

} // namespace niu2x::uv

#endif