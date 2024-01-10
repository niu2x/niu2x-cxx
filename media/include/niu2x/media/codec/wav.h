#ifndef NIU2X_MEDIA_CODEC_WAV_H
#define NIU2X_MEDIA_CODEC_WAV_H

#include <niu2x/media/codec/codec.h>

namespace niu2x::media {

class WavCodec : public SoundCodec {
public:
    WavCodec() { }
    virtual ~WavCodec() { }

    void encode(const SoundData&, ByteWriteStream* output) const override;
    SoundData decode(ByteReadStream* input) const override;
};

} // namespace niu2x::media

#endif