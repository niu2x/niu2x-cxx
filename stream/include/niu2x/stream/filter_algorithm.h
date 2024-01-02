#ifndef NIU2X_STREAM_FILTER_ALG_H
#define NIU2X_STREAM_FILTER_ALG_H

#include <niu2x/type.h>

namespace niu2x::stream {

class FilterAlgorithm {
public:
    using Output = std::function<void(const void* buf, size_t size)>;
    FilterAlgorithm() { }
    virtual ~FilterAlgorithm() { }
    virtual void write(const void* buf, size_t size, Output output) = 0;
    virtual void finalize(Output output) = 0;
    virtual void reset() = 0;
};

}; // namespace niu2x::stream

#endif
