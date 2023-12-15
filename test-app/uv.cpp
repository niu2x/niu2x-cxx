#include <niu2x/uv.h>

using namespace niu2x;

int main()
{
    int counter = 0;
    int counter2 = 0;
    uv::Loop loop;
    // uv::Idle idle(&loop, [&idle, &counter]() {
    //     printf("counter %d\n", counter);
    //     if (counter++ > 5) {
    //         idle.stop();
    //     }
    // });
    // idle.start();

    // uv::Timer timer(
    //     &loop,
    //     [&timer, &counter2]() {
    //         printf("counter2 %d\n", counter2);
    //         if (counter2++ > 5) {
    //             timer.stop();
    //         }
    //     },
    //     1);
    // timer.start();

    {
        uv::Process process(
            &loop,
            { "sleep", { "sleep", "30" } },
            [](int64_t status) { printf("ls exit status: %ld\n", status); });
    }

    loop.run_loop();
    return 0;
}