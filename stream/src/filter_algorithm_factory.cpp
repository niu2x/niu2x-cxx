#include "filter_algorithm_factory.h"
#include "filter_alg/md5.h"
#include "filter_alg/sha256.h"
#include <niu2x/exception.h>

namespace niu2x::stream {

UniquePtr<FilterAlgorithm> FilterAlgorithmFactory::create_obj(FilterType type)
{
    switch (type) {
        case FilterType::MD5: {
            return make_unique<filter_alg::MD5>();
        }
        case FilterType::SHA256: {
            return make_unique<filter_alg::SHA256>();
        }
    }
    throw_runtime_err("unsupport filter algorithm");
    return nullptr;
}

} // namespace niu2x::stream