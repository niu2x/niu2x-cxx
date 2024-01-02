#ifndef NIU2X_STREAM_FILTER_ALG_SHA256_H
    #define NIU2X_STREAM_FILTER_ALG_MD5_H

    #include <niu2x/stream/filter_algorithm.h>
    #include <niu2x/crypto/sha256.h>

namespace niu2x::stream::filter_alg {

class SHA256 : public FilterAlgorithm {
public:
    SHA256() { }
    virtual ~SHA256() { }
    virtual void write(const void* buf, size_t size, Output output) override;
    virtual void finalize(Output output) override;
    virtual void reset() override;

private:
    crypto::SHA256 imp_;
};

} // namespace niu2x::stream::filter_alg

#endif