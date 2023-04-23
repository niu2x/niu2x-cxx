#include <nxc/nxc.h>

using namespace nxc;

int main()
{
    auto stream_factory = NXC_MAKE_PTR(DefaultStreamFactory);
    auto archive_factory = NXC_MAKE_PTR(DefaultArchiveFactory);
    auto archive = archive_factory->create("./test.zip");

    return 0;
}