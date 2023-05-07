#include <gtest/gtest.h>

#include <nxc/nxc.h>

#define BYTES(a, b, c, d, e, f, g, h)                                          \
    0x##a, 0x##b, 0x##c, 0x##d, 0x##e, 0x##f, 0x##g, 0x##h,
unsigned long test_zip_length = 0xaf;

unsigned char test_zip[] = { BYTES(50, 4b, 3, 4, a, 0, 0, 0) BYTES(0, 0, 56, b3,
    9e, 56, b4, af) BYTES(d7, 1, d, 0, 0, 0, d, 0) BYTES(0, 0, 6, 0, 1c, 0, 52,
    45) BYTES(41, 44, 4d, 45, 55, 54, 9, 0) BYTES(3, a4, 7a, 4e, 64, be, 7a, 4e)
        BYTES(64, 75, 78, b, 0, 1, 4, e8) BYTES(3, 0, 0, 4, e8, 3, 0, 0) BYTES(
            68, 65, 6c, 6c, 6f, 20, 77, 6f) BYTES(72, 6c, 64, 21, a, 50, 4b, 1)
            BYTES(2, 1e, 3, a, 0, 0, 0, 0) BYTES(0, 56, b3, 9e, 56, b4, af, d7)
                BYTES(1, d, 0, 0, 0, d, 0, 0) BYTES(0, 6, 0, 18, 0, 0, 0, 0)
                    BYTES(0, 1, 0, 0, 0, b4, 81, 0) BYTES(0, 0, 0, 52, 45, 41,
                        44, 4d) BYTES(45, 55, 54, 5, 0, 3, a4, 7a) BYTES(4e, 64,
                        75, 78, b, 0, 1, 4) BYTES(e8, 3, 0, 0, 4, e8, 3, 0)
                        BYTES(0, 50, 4b, 5, 6, 0, 0, 0) BYTES(0, 1, 0, 1, 0, 4c,
                            0, 0) BYTES(0, 4d, 0, 0, 0, 0, 0, 0) 0x0 };

using namespace nxc;

int main()
{
    auto archive_factory = ArchiveFactory::get();
    Buffer buffer;
    buffer.write(test_zip, test_zip_length);
    auto archive = *archive_factory->create(&buffer);
    archive->open(OpenMode::READ);
    {
        auto stream = archive->read_entry("README");
        Buffer output;
        pipe(*stream, *StreamFactory::get()->create_write_stream(output));
        EXPECT_STREQ((const char*)output.data(), "hello world!\n");
    }
    archive->close();

    return 0;
}