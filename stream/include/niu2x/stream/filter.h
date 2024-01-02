#ifndef NIU2X_STREAM_FILTER_H
#define NIU2X_STREAM_FILTER_H

#include <niu2x/base_stream.h>
#include <niu2x/stream/filter_algorithm.h>
#include <niu2x/stream/filter_type.h>

namespace niu2x::stream {

class ByteWriteFilter : public ByteWriteStream {
public:
    ByteWriteFilter(FilterType filter_type, ByteWriteStream* next);
    ByteWriteFilter(const String& filter_type, ByteWriteStream* next);
    ByteWriteFilter(UniquePtr<FilterAlgorithm> filter, ByteWriteStream* next);

    virtual ~ByteWriteFilter();
    virtual void write(const uint8_t* buf, size_t size) override;
    virtual void finalize() override;

private:
    FilterAlgorithm::Output delegate_;

    ByteWriteStream* next_;
    UniquePtr<FilterAlgorithm> filter_alg_;
};

}; // namespace niu2x::stream

#endif
