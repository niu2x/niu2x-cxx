#ifndef NIU2X_MEDIA_SOUND_H
#define NIU2X_MEDIA_SOUND_H

#include <niu2x/std_alias.h>
#include <niu2x/convention.h>
#include <niu2x/resource.h>

namespace niu2x::media {

using SampleValue = double;

struct SoundData {
    Vector<SampleValue> samples;
    int sample_bits;
    int sample_frequency;
};

double Sound_duration(SoundData* self);

} // namespace niu2x::media

#endif