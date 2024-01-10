#include <niu2x/base_stream.h>
#include <niu2x/exception.h>

namespace niu2x {

uint32_t ByteReadStream::read_u32()
{
    uint32_t n;
    if (read(&n, 4) != 4) {
        throw_runtime_err("no more bytes");
    }
    return n;
}
uint8_t ByteReadStream::read_u8()
{
    uint32_t n;
    if (read(&n, 1) != 1) {
        throw_runtime_err("no more bytes");
    }
    return n;
}
void ByteReadStream::read_char(char* buf, NR size)
{
    if (read(buf, size) != size) {
        throw_runtime_err("no more bytes");
    }
}

} // namespace niu2x