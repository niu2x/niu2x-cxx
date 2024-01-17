#include <niu2x/base_stream.h>
#include <niu2x/exception.h>

namespace niu2x {

void ByteReadStream::read_char(char* buf, NR size)
{
    if (read(buf, size) != size) {
        throw_runtime_err("no more bytes");
    }
}

void ByteWriteStream::write_char(const char* buf, NR size) { write(buf, size); }

} // namespace niu2x