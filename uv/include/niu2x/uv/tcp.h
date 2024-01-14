#ifndef NIU2X_UV_TCP_H
#define NIU2X_UV_TCP_H

#include <niu2x/noncopyable.h>
#include <niu2x/uv/exception.h>
#include <niu2x/malloc_handle.h>

namespace niu2x::uv {

class Loop;

class TCP : private Noncopyable {
public:
    using CONNECT_CB = Function<void(UniquePtr<TCP>)>;
    TCP(Loop* loop);
    ~TCP();
    void* native() const { return native_.data(); }
    void bind(const String& ip, uint16_t port);
    void listen(CONNECT_CB cb);
    void accept(TCP* server);

private:
    MallocHandle native_;
    Loop* loop_;
    CONNECT_CB connect_cb_;
    static void uv_connection_cb(void* server, int status);
    void notify_connection();
};

} // namespace niu2x::uv

#endif