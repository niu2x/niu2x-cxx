#include <niu2x/stream.h>
#include <niu2x/fs.h>

using namespace niu2x;

int main(int argc, char* argv[])
{
    fs::File input_file(argv[1]);
    stream::FileReadStream ins(input_file);

    Buffer buffer;
    stream::BufferWriteStream outs(buffer);
    stream::WriteFilter md5_filter(stream::FilterType::MD5, &outs);

    uint8_t block[1024];
    while (!ins.eof()) {
        auto size = ins.read(block, 1024);
        if (size > 0) {
            md5_filter.write(block, size);
        }
    }
    md5_filter.finalize();

    printf("%s\n", buffer.str().c_str());

    return 0;
}