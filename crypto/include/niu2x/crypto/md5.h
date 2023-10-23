#ifndef NIU2X_CRYPTO_MD5_H
#define NIU2X_CRYPTO_MD5_H

#include <niu2x/crypto/digest.h>

namespace niu2x::crypto {

class NXAPI MD5 : public Digest {
public:
    MD5();
    ~MD5();
    void reset() override;
    void update(const void* data, size_t size) override;
    void finalize() override;
    const Span<const uint8_t> digest() const override
    {
        return Span<const uint8_t>(digest_);
    }

private:
    uint64_t size_; // Size of input in bytes
    uint32_t buffer_[4]; // Current accumulation of hash
    uint8_t input_[64]; // Input to be used in the next step
    uint8_t digest_[16]; // Result of algorithm

    void step(uint32_t* buffer, const uint32_t* input);
};

} // namespace niu2x::crypto

#endif