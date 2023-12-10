#include <niu2x/uv.h>

using namespace niu2x;

int main()
{
    uv::Loop loop;
    auto idle = loop.create_idle();
    int counter = 0;
    loop.idle_start(idle, [&loop, &idle, &counter]() {
        printf("counter %d\n", counter);
        if (counter++ > 5) {
            loop.idle_stop(idle);
            loop.destroy_idle(idle);
        }
    });
    loop.run();
    loop.close();
    return 0;
}