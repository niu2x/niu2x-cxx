#ifndef NIU2X_CRYPTO_DIGEST_H
#define NIU2X_CRYPTO_DIGEST_H

#include <niu2x/type.h>
namespace niu2x::crypto {

class DigestAlgorithm {
public:
    using SpanDigest = Span<const uint8_t>;

    virtual ~DigestAlgorithm() { }
    virtual void reset() = 0;
    virtual void update(const void* data, size_t size) = 0;
    virtual void finalize() = 0;
    virtual SpanDigest digest() const = 0;
};

} // namespace niu2x::crypto

#endif