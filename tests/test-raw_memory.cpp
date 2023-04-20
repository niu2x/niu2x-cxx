#include <nxc/nxc.h>

int main()
{
    static uint8_t buffer[128];
    auto mem = NXC_MAKE_PTR(nxc::RawMemory, buffer, 128);
    auto mem1 = mem;
    auto mem2 = mem;

    auto read = NXC_MAKE_PTR(nxc::RawMemory, buffer, 128);
    auto c = read->data()[0];

    nxc::ConstRawMemoryPtr read1 = NXC_MAKE_PTR(nxc::RawMemory, buffer, 128);
    auto c1 = read1->data()[0];

    const auto write1 = NXC_MAKE_PTR(nxc::RawMemory, buffer, 128);
    write1->data()[0] = 0;

    return 0;
}