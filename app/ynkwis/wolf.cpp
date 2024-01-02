#include <niu2x/uv.h>

using namespace niu2x;

int main()
{
    uv::Loop uv_loop;
    uv::TCP listen_sock(&uv_loop);
    listen_sock.bind("127.0.0.1", 8082);
    uv_loop.run_loop();
    return 0;
}