#include "md5.h"
#include <niu2x/unused.h>

namespace niu2x::stream::filter_alg {

void MD5::write(const void* buf, size_t size, Output output)
{
    unused(output);
    imp_.update(buf, size);
}

static const char hex_digits[] = "0123456789abcdef";

void MD5::finalize(Output output)
{
    imp_.finalize();

    char digest_sz[32];
    auto digest = imp_.digest();
    int i = 0;
    while (i < 16) {
        digest_sz[(i << 1)] = hex_digits[digest[i] >> 4];
        digest_sz[(i << 1) + 1] = hex_digits[digest[i] & 0xF];
        i++;
    }

    output(digest_sz, 32);
}

void MD5::reset() { imp_.reset(); }

} // namespace niu2x::stream::filter_alg