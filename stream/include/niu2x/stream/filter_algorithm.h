#ifndef NIU2X_STREAM_FILTER_ALG_H
#define NIU2X_STREAM_FILTER_ALG_H

#include <niu2x/std_alias.h>
namespace niu2x::stream {

class FilterAlgorithm {
public:
    using Output = Function<void(const uint8_t* buf, size_t size)>;
    FilterAlgorithm() { }
    virtual ~FilterAlgorithm() { }
    virtual void write(const uint8_t* buf, size_t size, Output output) = 0;
    virtual void finalize(Output output) = 0;
    virtual void reset() = 0;
};

}; // namespace niu2x::stream

#endif
