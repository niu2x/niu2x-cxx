#include <nxc/nxc.h>

using namespace nxc;

int main()
{
    auto stream_factory = StreamFactory::get();
    auto os = stream_factory->create_write_stream(String("./test.txt"));
    for (int i = 0; i < 1024; i++)
        NXC_ASSERT((*os)->write("Hello world!", 12), "write failed");

    return 0;
}