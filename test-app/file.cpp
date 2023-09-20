#include <niu2x/stream.h>

using namespace niu2x;

int main(int argc, char* argv[])
{
    fs::File file("./test.txt");
    printf("exists: %d\n", file.exists());

    stream::FileWriteStream output(file);
    output.write("Hello world", 11);

    Buffer buffer;
    stream::BufferWriteStream os(buffer);
    os.write("hello stream", 12);

    auto msg = buffer.str();

    output.write(msg.c_str(), msg.size());

    return 0;
}