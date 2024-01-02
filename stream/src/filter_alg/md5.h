#ifndef NIU2X_STREAM_FILTER_ALG_MD5_H
#define NIU2X_STREAM_FILTER_ALG_MD5_H

#include <niu2x/stream/filter_algorithm.h>
#include <niu2x/crypto/md5.h>

namespace niu2x::stream::filter_alg {

class MD5 : public FilterAlgorithm {
public:
    MD5() { }
    virtual ~MD5() { }
    virtual void write(const uint8_t* buf, size_t size, Output output) override;
    virtual void finalize(Output output) override;
    virtual void reset() override;

private:
    crypto::MD5 imp_;
};

} // namespace niu2x::stream::filter_alg

#endif