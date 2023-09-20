#ifndef NIU2X_CRYPTO_MD5_H
#define NIU2X_CRYPTO_MD5_H

#include <niu2x/type.h>

namespace niu2x::crypto {

class NXAPI MD5 {
public:
    MD5();
    ~MD5();
    void reset();
    void update(void* data, size_t size);

private:
    union {
        uint8_t buf[64];
        uint32_t buf_w[16];
    } buf_;
    uint32_t hash_[4];
    uint32_t len_high_;
    uint32_t len_low_;
};

} // namespace niu2x::crypto

#endif