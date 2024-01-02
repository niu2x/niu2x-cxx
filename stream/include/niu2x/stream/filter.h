#ifndef NIU2X_STREAM_FILTER_H
#define NIU2X_STREAM_FILTER_H

#include <niu2x/base_stream.h>
#include <niu2x/stream/filter_algorithm.h>
#include <niu2x/stream/filter_type.h>

namespace niu2x::stream {

class WriteFilter : public ByteWriteStream {
public:
    WriteFilter(FilterType filter_type, ByteWriteStream* next);
    virtual ~WriteFilter();
    virtual void write(const uint8_t* buf, size_t size) override;
    virtual void finalize() override;

private:
    FilterAlgorithm::Output delegate_;

    ByteWriteStream* next_;
    UniquePtr<FilterAlgorithm> filter_alg_;
};

}; // namespace niu2x::stream

#endif
