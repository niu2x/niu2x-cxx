#include <niu2x/stream.h>

using namespace niu2x;

int main(int argc, char* argv[])
{
    fs::File file("./test.txt");
    printf("exists: %d\n", file.exists());

    stream::FileWriteStream out(file);
    out.write("Hello world", 11);

    return 0;
}