#ifndef NIU2X_MEDIA_CODEC_CODEC_H
#define NIU2X_MEDIA_CODEC_CODEC_H

#include <niu2x/media/type.h>
namespace niu2x::media {

class SoundCodec {
public:
    SoundCodec() { }
    virtual ~SoundCodec() { }

    virtual void encode(const SoundData&, ByteWriteStream* output) const = 0;
    virtual SoundData decode(ByteReadStream* input) const = 0;

    // int sample_freq() const { return sample_freq_; }
    // int sample_bits() const { return sample_bits_; }

    // void set_sample_freq(int s) { sample_freq_ = s; }
    // void set_sample_bits(int s) { sample_bits_ = s; }

private:
    // int sample_freq_ = 1;
    // int sample_bits_ = 8;
};

}; // namespace niu2x::media

#endif