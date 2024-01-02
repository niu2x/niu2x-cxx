#include "uv.h"
#include <niu2x/uv/tcp.h>
#include <niu2x/uv/loop.h>
#include <string.h>
#include "helper.h"

namespace niu2x::uv {

TCP::TCP(Loop* loop)
: native_(sizeof(uv_tcp_t))
, loop_(loop)
{
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
}

} // namespace niu2x::uv