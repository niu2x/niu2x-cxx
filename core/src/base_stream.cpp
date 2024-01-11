#include <niu2x/base_stream.h>
#include <niu2x/exception.h>

namespace niu2x {

void ByteReadStream::read_char(char* buf, NR size)
{
    if (read(buf, size) != size) {
        throw_runtime_err("no more bytes");
    }
}

} // namespace niu2x