#include <niu2x/stream/filter.h>

#include "filter_algorithm_factory.h"

namespace niu2x::stream {

ByteWriteFilter::ByteWriteFilter(FilterType filter_type, WriteStream* next)
: next_(next)
, filter_alg_(FilterAlgorithmFactory::get()->create_obj(filter_type))
{
    delegate_ = [this] (const uint8_t* buf, size_t size) { 
        next_->write(buf, size); 
    };
}

ByteWriteFilter::ByteWriteFilter(
    const String& filter_type,
    ByteWriteStream* next)
: next_(next)
, filter_alg_(FilterAlgorithmFactory::get()->create_obj(filter_type))
{
    delegate_ = [this] (const uint8_t* buf, size_t size) { 
        next_->write(buf, size); 
    };
}

ByteWriteFilter::~ByteWriteFilter() { }

void ByteWriteFilter::write(const uint8_t* buf, size_t size)
{
    filter_alg_->write(buf, size, delegate_);
}

void ByteWriteFilter::finalize()
{
    filter_alg_->finalize(delegate_);
    next_->finalize();
}

} // namespace niu2x::stream