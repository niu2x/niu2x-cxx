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

    int sample_rate() const { return sample_rate_; }
    int sample_width() const { return sample_width_; }

    void set_sample_rate(int s) { sample_rate_ = s; }
    void set_sample_width(int s) { sample_width_ = s; }

private:
    int sample_rate_ = 1;
    int sample_width_ = 1;
};

}; // namespace niu2x::media

#endif