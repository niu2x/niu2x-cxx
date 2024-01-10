#include <niu2x/media/codec/wav.h>
#include <niu2x/unused.h>

namespace niu2x::media {

void WavCodec::encode(const SoundData&, ByteWriteStream* output) const
{
    unused(output);
}

SoundData WavCodec::decode(ByteReadStream* input) const
{
    unused(input);
    return {};
}

} // namespace niu2x::media