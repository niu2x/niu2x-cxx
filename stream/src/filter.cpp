#include <niu2x/stream/filter.h>

#include "filter_algorithm_factory.h"

namespace niu2x::stream {

WriteFilter::WriteFilter(FilterType filter_type, WriteStream* next)
: next_(next)
, filter_alg_(FilterAlgorithmFactory::create_algorithm(filter_type))
{
}

WriteFilter::~WriteFilter() { }

void WriteFilter::write(const void* buf, size_t size)
{
    filter_alg_->write(buf, size,
        [this](const void* buf, size_t size) { next_->write(buf, size); });
}

void WriteFilter::finalize()
{
    filter_alg_->finalize(
        [this](const void* buf, size_t size) { next_->write(buf, size); });

    next_->finalize();
}

} // namespace niu2x::stream