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
    using READ_CB = Function<void(const uint8_t* buf, NR size)>;
    TCP(Loop* loop);
    ~TCP();
    void* native() const { return native_.data(); }
    void bind(const String& ip, uint16_t port);
    void listen(CONNECT_CB cb);
    void accept(TCP* server);
    // void write(const void *, NR size);
    void read_start(READ_CB);
    void read_stop();

private:
    MallocHandle native_;
    Loop* loop_;
    CONNECT_CB connect_cb_;
    READ_CB read_cb_;
    static void uv_connection_cb(void* server, int status);
    static void uv_read_cb(void* stream, ssize_t nread, const void* buf);

    void notify_connection();
    void notify_read_data(const uint8_t* buf, NR size);
    void notify_read_eof();
};

} // namespace niu2x::uv

#endif