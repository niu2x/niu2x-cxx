#include <nxc/nxc.h>

int main()
{
    static uint8_t buffer[16];
    auto file_factory = nxc::FileFactory::get();

    auto mem = NXC_MAKE_PTR(nxc::RawMemory, buffer, 16);

    auto mem_file = file_factory->create(mem);
    mem_file->open(nxc::OpenMode::WRITE);

    char c = 'a';
    nxc::Result<size_t> err;
    do {
        err = mem_file->write(&c, 1);
        c++;
    } while (err);

    auto mem_read_file = file_factory->create(mem);
    char buff[256] = { 0 };
    err = mem_read_file->read(buff, 256);
    if (err)
        printf("%ld %s\n", *err, buff);

    return 0;
}