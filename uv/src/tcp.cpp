#include "uv.h"
#include <niu2x/uv/tcp.h>
#include <niu2x/uv/loop.h>
#include <niu2x/logger.h>
#include <niu2x/unused.h>
#include <string.h>
#include "helper.h"

namespace niu2x::uv {

TCP::TCP(Loop* loop)
: native_(sizeof(uv_tcp_t))
, loop_(loop)
{
    logger << "TCP::TCP\n";
    auto uv_tcp = UV_TYPE(uv_tcp_t*, native_.data());
    memset(uv_tcp, 0, sizeof(uv_tcp_t));

    auto uv_loop = reinterpret_cast<uv_loop_t*>(loop->native());
    uv_tcp_init(uv_loop, uv_tcp);
    uv_tcp->data = this;
}

void TCP::bind(const String& ip, uint16_t port)
{
    struct sockaddr_in addr;
    uv_ip4_addr(ip.c_str(), port, &addr);
    auto uv_tcp = UV_TYPE(uv_tcp_t*, native_.data());
    uv_tcp_bind(uv_tcp, (sockaddr*)&addr, 0);
}

TCP::~TCP()
{
    auto uv_tcp = UV_TYPE(uv_tcp_t*, native_.data());
    // UV_ENSURE_STOP(uv_tcp, uv_tcp_stop);
    UV_ENSURE_CLOSE(uv_tcp, loop_);
    logger << "TCP::~TCP\n";
}

void TCP::listen(CONNECT_CB cb)
{
    connect_cb_ = cb;

    auto uv_tcp = UV_TYPE(uv_tcp_t*, native_.data());

    using CALLBACK_T = void (*)(uv_stream_t*, int);

    int r = uv_listen(
        (uv_stream_t*)uv_tcp,
        4,
        (CALLBACK_T)&TCP::uv_connection_cb);

    if (r) {
        throw_runtime_err("Listen error " + String(uv_strerror(r)));
    }
}

void TCP::uv_connection_cb(void* p_server, int status)
{
    auto uv_tcp = UV_TYPE(uv_tcp_t*, p_server);
    auto tcp = reinterpret_cast<TCP*>(uv_tcp->data);
    if (status == 0) {
        tcp->notify_connection();
    }
}

void TCP::notify_connection()
{
    logger << "notify_connection\n";
    UniquePtr<TCP> client;
    try {
        client = make_unique<TCP>(loop_);
        client->accept(this);
    } catch (...) {
        logger << "accept client fail\n";
        client.reset();
    }
    if (client) {
        connect_cb_(move(client));
    }
}

void TCP::accept(TCP* server)
{
    auto uv_server = (uv_stream_t*)(server->native());
    auto uv_client = (uv_stream_t*)(native());
    CHECK_UV_ERR(uv_accept(uv_server, uv_client));
}

static void alloc_cb(uv_handle_t* handle, size_t suggested_size, uv_buf_t* buf)
{
    unused(handle);
    buf->base = (char*)malloc(suggested_size);
    buf->len = suggested_size;
}

void TCP::uv_read_cb(void* p_server, ssize_t nread, const void* p_buf)
{
    auto buf = (uv_buf_t*)p_buf;
    auto uv_tcp = UV_TYPE(uv_tcp_t*, p_server);
    auto tcp = reinterpret_cast<TCP*>(uv_tcp->data);
    if (nread > 0) {
        tcp->notify_read_data((const uint8_t*)buf->base, buf->len);
        free(buf->base);
    } else {
        tcp->notify_read_eof();
    }
}

void TCP::read_start(READ_CB cb)
{
    read_cb_ = cb;
    auto uv_tcp = UV_TYPE(uv_tcp_t*, native_.data());
    using CALLBACK_T
        = void (*)(uv_stream_t * stream, ssize_t nread, const uv_buf_t* buf);
    CHECK_UV_ERR(uv_read_start(
        (uv_stream_t*)uv_tcp,
        &alloc_cb,
        (CALLBACK_T)&TCP::uv_read_cb));
}

void TCP::notify_read_data(const uint8_t* buf, NR size) { read_cb_(buf, size); }
void TCP::notify_read_eof() { read_cb_(nullptr, 0); }

} // namespace niu2x::uv