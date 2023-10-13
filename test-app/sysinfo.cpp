#include <stdio.h>
#include <niu2x/bit.h>

using namespace niu2x;

int main(int argc, char* argv[])
{
    if (endian::little) {
        printf("endian: little\n");
    }

    if (endian::big) {
        printf("endian: big\n");
    }

    return 0;
}