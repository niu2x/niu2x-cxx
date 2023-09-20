#include <niu2x/crypto/md5.h>
#include <niu2x/bit.h>

namespace niu2x::crypto {

void pp_crypto_hash_md5_swap_bytes(uint32_t* data, int words)
{
    if (endian::big) {

        while (words-- > 0) {
            // *data = PUINT32_TO_LE(*data);
            ++data;
        }
    }
}

MD5::MD5() { reset(); }
MD5::~MD5() { }

void MD5::reset()
{
    memset(buf_.buf, 0, 64);

    len_low_ = 0;
    len_high_ = 0;

    hash_[0] = 0x67452301;
    hash_[1] = 0xEFCDAB89;
    hash_[2] = 0x98BADCFE;
    hash_[3] = 0x10325476;
}

void MD5::update(void* data, size_t size)
{
    (void)data;
    (void)size;
    // uint32_t left, to_fill;

    // left = len_low_ & 0x3F;
    // to_fill = 64 - left;

    // len_low_ += (uint32_t)len;

    // if (len_low_ < (uint32_t)len)
    //     ++len_high_;

    // if (left && (uint32_t)len >= to_fill) {
    //     memcpy(buf_.buf + left, data, to_fill);
    //     swap_bytes(buf_.buf_w, 16);
    //     pp_crypto_hash_md5_process(buf_.buf_w);

    //     data += to_fill;
    //     len -= to_fill;
    //     left = 0;
    // }

    // while (len >= 64) {
    //     memcpy(buf_.buf, data, 64);
    //     swap_bytes(buf_.buf_w, 16);
    //     pp_crypto_hash_md5_process(buf_.buf_w);

    //     data += 64;
    //     len -= 64;
    // }

    // if (len > 0)
    //     memcpy(buf_.buf + left, data, len);
}

} // namespace niu2x::crypto
