#ifndef NIU2X_CRYPTO_SHA256_H
#define NIU2X_CRYPTO_SHA256_H

#include <niu2x/type.h>

namespace niu2x::crypto {

class NXAPI SHA256 {
public:
    SHA256();
    ~SHA256();
    void reset();
    void update(const void* data, size_t size);
    void finalize();
    const uint8_t* digest() const { return digest_; }

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