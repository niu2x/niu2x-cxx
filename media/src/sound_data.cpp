#include <niu2x/media/type.h>

namespace niu2x::media {

double Sound_duration(const SoundData& sound)
{
    double samples_nr = sound.channels[0].size();
    double duration = samples_nr / sound.sample_frequency;
    return duration;
}

SoundData Sound_crop(const SoundData& sound, double start, double duration)
{
    Index frame_start = start * sound.sample_frequency;
    Index frame_end = sound.channels[0].size();

    if (duration > 0) {
        Index tmp_end = (start + duration) * sound.sample_frequency + 1;
        frame_end = min(frame_end, tmp_end);
    }

    SoundData result;

    result.sample_frequency = sound.sample_frequency;
    result.sample_bits = sound.sample_bits;

    for (auto& channel : sound.channels) {
        auto iter_begin = channel.begin();
        auto first = iter_begin + frame_start;
        auto last = iter_begin + frame_end;
        result.channels.push_back(Vector<SampleValue>(first, last));
    }

    return result;
}

} // namespace niu2x::media