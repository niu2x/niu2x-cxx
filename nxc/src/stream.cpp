#include <nxc/stream.h>

namespace nxc {

ReadStream::ReadStream() { }
ReadStream::~ReadStream() { }

Result<size_t> ReadStream::read(void* buf, size_t n)
{
    uint8_t* buffer = (uint8_t*)buf;

    size_t total_bytes = 0;
    do {
        auto result = _read(buffer + total_bytes, n - total_bytes);
        if (result) {
            total_bytes += *result;
        } else {

            if (result.error() != E::END_OF_FILE) {
                return result;
            }

            if (!total_bytes) {
                return result;
            }

            break;
        }
    } while (total_bytes < n);

    return total_bytes;
}

Result<char> ReadStream::read_char()
{
    char c;
    auto ret = read(&c, 1);
    if (ret) {
        return c;
    }
    return ret;
}

Result<size_t> WriteStream::write(const void* buf, size_t n)
{
    size_t total_bytes = 0;

    const uint8_t* buffer = (uint8_t*)buf;
    do {
        auto result = _write(buffer + total_bytes, n - total_bytes);
        if (result) {
            total_bytes += *result;
        } else {
            return result;
        }
    } while (total_bytes < n);

    return total_bytes;
}

Result<size_t> WriteStream::write(const void* buf)
{
    return write(buf, strlen((const char*)buf));
}

WriteStream::WriteStream() { }
WriteStream::~WriteStream() { }

} // namespace nxc