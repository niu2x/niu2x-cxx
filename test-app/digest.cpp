#include <niu2x/stream.h>
#include <niu2x/fs.h>

using namespace niu2x;

int main(int argc, char* argv[])
{

    fs::File input_file(argv[2]);
    stream::FileReadStream ins(input_file);

    Buffer buffer;
    stream::BufferWriteStream outs(buffer);

    stream::FilterType alg;
    String alg_name = argv[1];
    if (alg_name == "md5")
        alg = stream::FilterType::MD5;
    else if (alg_name == "sha256")
        alg = stream::FilterType::SHA256;

    stream::WriteFilter filter(alg, &outs);

    uint8_t block[1024];
    while (!ins.eof()) {
        auto size = ins.read(block, 1024);
        if (size > 0) {
            filter.write(block, size);
        }
    }
    filter.finalize();

    printf("%s\n", buffer.str().c_str());

    return 0;
}