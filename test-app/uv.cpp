#include <niu2x/uv.h>

using namespace niu2x;

int main()
{
    int counter = 0;
    uv2::Loop loop;
    uv2::Idle idle(&loop, [&idle, &counter]() {
        printf("counter %d\n", counter);
        if (counter++ > 5) {
            idle.stop();
        }
    });
    idle.start();
    loop.run_loop();
    return 0;
}