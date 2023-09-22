#ifndef NIU2X_STREAM_FILTER_H
#define NIU2X_STREAM_FILTER_H

#include <niu2x/type.h>
#include <niu2x/stream/filter_algorithm.h>
#include <niu2x/stream/filter_type.h>

namespace niu2x::stream {

class NXAPI WriteFilter : public WriteStream {
public:
    WriteFilter(FilterType filter_type, WriteStream* next);
    virtual ~WriteFilter();
    virtual void write(const void* buf, size_t size) override;
    virtual void finalize() override;

private:
    WriteStream* next_;
    UniquePtr<FilterAlgorithm> filter_alg_;
};

}; // namespace niu2x::stream

#endif
