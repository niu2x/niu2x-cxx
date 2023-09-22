#include <niu2x/image.h>
#include <niu2x/fs.h>
#include <niu2x/stream.h>

using namespace niu2x;

int main(int argc, char* argv[])
{
    Image image;
    fs::File image_file(argv[1]);
    stream::FileReadStream image_in(image_file);
    image.load_from(&image_in);

    fs::File out_file(argv[2]);
    stream::FileWriteStream image_out(out_file);
    image.store_to(&image_out);
    image_out.finalize();

    return 0;
}