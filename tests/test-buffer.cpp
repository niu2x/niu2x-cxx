#include <nxc/nxc.h>

using namespace nxc;

int main()
{

    Buffer buffer;
    buffer.resize(1024);

    for (int i = 0; i < buffer.size(); i++) {
        buffer.data()[i] = i % 256;
    }

    buffer.resize(16);

    for (int i = 0; i < buffer.size(); i++) {
        printf("buffer.data()[i] %d\n", buffer.data()[i]);
    }

    return 0;
}