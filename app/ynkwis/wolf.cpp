#include <niu2x/uv.h>

using namespace niu2x;

int main()
{
    uv::Loop uv_loop;
    uv_loop.run_loop();
    return 0;
}