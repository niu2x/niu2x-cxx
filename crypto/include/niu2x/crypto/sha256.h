#ifndef NIU2X_CRYPTO_SHA256_H
#define NIU2X_CRYPTO_SHA256_H

#include <niu2x/crypto/digest_algorithm.h>

namespace niu2x::crypto {

class SHA256 : public DigestAlgorithm {
public:
    SHA256();
    ~SHA256();
    void reset() override;
    void update(const void* data, size_t size) override;
    void finalize() override;
    Digest digest() const override { return Digest(digest_); }

private:
    uint64_t bit_len_;
    uint32_t data_len_;
    uint32_t state_[8];
    uint8_t data_[64];
    uint8_t digest_[32];

    void step(const uint8_t data[]);
};

} // namespace niu2x::crypto

#endif