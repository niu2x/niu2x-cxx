#ifndef NIU2X_CRYPTO_DIGEST_H
#define NIU2X_CRYPTO_DIGEST_H

#include <niu2x/type.h>
namespace niu2x::crypto {

class Digest {
public:
    virtual ~Digest() { }
    virtual void reset() = 0;
    virtual void update(const void* data, size_t size) = 0;
    virtual void finalize() = 0;
    virtual const Span<const uint8_t> digest() const = 0;
};

} // namespace niu2x::crypto

#endif