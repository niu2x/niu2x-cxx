#include <niu2x/fs.h>

int main(int argc, char* argv[])
{
    niu2x::fs::create_dir(niu2x::fs::Path(argv[1]));
    return 0;
}