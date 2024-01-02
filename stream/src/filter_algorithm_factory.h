#ifndef NIU2X_STREAM_FILTER_ALGORITHM_FACTORY_H
#define NIU2X_STREAM_FILTER_ALGORITHM_FACTORY_H

#include <niu2x/factory.h>
#include <niu2x/singleton.h>
#include <niu2x/stream/filter_algorithm.h>
#include <niu2x/stream/filter_type.h>

namespace niu2x::stream {

class FilterAlgorithmFactory : public UPtrFactory<FilterAlgorithm>,
                               public Singleton<FilterAlgorithmFactory> {
public:
    UniquePtr<FilterAlgorithm> create_obj(const String& name) override;
    UniquePtr<FilterAlgorithm> create_obj(FilterType type);
};

} // namespace niu2x::stream

#endif