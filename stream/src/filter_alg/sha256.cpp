#include "sha256.h"
#include <niu2x/disable_windows_warning.h>
#include <niu2x/unused.h>

namespace niu2x::stream::filter_alg {

void SHA256::write(const void* buf, size_t size, Output output)
{
    unused(output);
    imp_.update(buf, size);
}

static const char hex_digits[] = "0123456789abcdef";

void SHA256::finalize(Output output)
{
    imp_.finalize();

    char digest_sz[64];
    auto digest = imp_.digest();
    Index i = 0;
    while (i < digest.size()) {
        digest_sz[(i << 1)] = hex_digits[digest[i] >> 4];
        digest_sz[(i << 1) + 1] = hex_digits[digest[i] & 0xF];
        i++;
    }
    output(digest_sz, 64);
}

void SHA256::reset() { imp_.reset(); }

} // namespace niu2x::stream::filter_alg