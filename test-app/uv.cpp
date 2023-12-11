#include <niu2x/uv.h>

using namespace niu2x;

int main()
{
    int counter = 0;
    int counter2 = 0;
    uv2::Loop loop;
    uv2::Idle idle(&loop, [&idle, &counter]() {
        printf("counter %d\n", counter);
        if (counter++ > 5) {
            idle.stop();
        }
    });
    idle.start();

    uv2::Timer timer(
        &loop,
        [&timer, &counter2]() {
            printf("counter2 %d\n", counter2);
            if (counter2++ > 5) {
                timer.stop();
            }
        },
        1);
    timer.start();

    loop.run_loop();
    return 0;
}