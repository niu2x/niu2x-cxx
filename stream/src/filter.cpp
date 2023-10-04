#include <niu2x/stream/filter.h>

#include "filter_algorithm_factory.h"

namespace niu2x::stream {

WriteFilter::WriteFilter(FilterType filter_type, WriteStream* next)
: next_(next)
, filter_alg_(FilterAlgorithmFactory::create_algorithm(filter_type))
{
    delegate_ = [this](const void* buf, size_t size) { 
        next_->write(buf, size); 
    };
}

WriteFilter::~WriteFilter() { }

void WriteFilter::write(const void* buf, size_t size)
{
    filter_alg_->write(buf, size, delegate_);
}

void WriteFilter::finalize()
{
    filter_alg_->finalize(delegate_);

    next_->finalize();
}

} // namespace niu2x::stream