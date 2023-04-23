#include <nxc/nxc.h>

using namespace nxc;

int main()
{
    StreamFactoryPtr stream_factory = NXC_MAKE_PTR(DefaultStreamFactory);
    stream_factory->set_file_factory(NXC_MAKE_PTR(DefaultFileFactory));
    auto os = stream_factory->create_write_stream(String("./test.txt"));
    for (int i = 0; i < 1024; i++)
        NXC_ASSERT(os->write("Hello world!", 12), "write failed");

    return 0;
}