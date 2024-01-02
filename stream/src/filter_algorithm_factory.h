#ifndef NIU2X_STREAM_FILTER_ALGORITHM_FACTORY_H
#define NIU2X_STREAM_FILTER_ALGORITHM_FACTORY_H

#include <niu2x/type.h>
#include <niu2x/stream/filter_algorithm.h>
#include <niu2x/stream/filter_type.h>

namespace niu2x::stream {

class FilterAlgorithmFactory {
public:
    static UniquePtr<FilterAlgorithm> create_algorithm(FilterType type);
};

} // namespace niu2x::stream

#endif