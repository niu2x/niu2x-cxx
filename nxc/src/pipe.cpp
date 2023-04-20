#include <nxc/pipe.h>
#include <nxc/buffer.h>

const auto buf_size = 4096;

namespace nxc {

Result<size_t> pipe(ReadStream* r, WriteStream* w)
{
    Buffer buffer;
    buffer.resize(buf_size);

    size_t bytes = 0;

    while (1) {

        auto read_result = r->read(buffer.data(), buffer.size());
        if (!read_result) {

            if (read_result.error() != E::END_OF_FILE) {
                return read_result;
            }

            break;
        }

        auto write_result = w->write(buffer.data(), *read_result);
        if (!write_result)
            return write_result;
    }

    return bytes;
}

} // namespace nxc