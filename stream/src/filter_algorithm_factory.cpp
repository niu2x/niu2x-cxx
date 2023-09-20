#include "filter_algorithm_factory.h"
#include "filter_alg/md5.h"

namespace niu2x::stream {

UniquePtr<FilterAlgorithm> FilterAlgorithmFactory::create_algorithm(
    FilterType type)
{
    switch (type) {
        case FilterType::MD5: {
            return make_unique<filter_alg::MD5>();
        }
    }
    throw_runtime_err("unsupport filter algorithm");
    return nullptr;
}

} // namespace niu2x::stream