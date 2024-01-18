#include <niu2x/media/type.h>
#include <niu2x/unused.h>

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
        frame_end = std::min(frame_end, tmp_end);
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

SoundData Sound_change_speed(const SoundData& sound, double scale)
{
    SoundData result;
    result.sample_frequency = sound.sample_frequency;
    result.sample_bits = sound.sample_bits;
    int repeat_cycle = 5000;
    int repeat_samples_nr = repeat_cycle / scale - repeat_cycle;

    for (auto& channel : sound.channels) {

        Vector<SampleValue> new_channel;

        auto end = channel.end();
        for (auto i = channel.begin(); i != end; i += repeat_cycle) {
            int count = 0;
            if (std::distance(i, end) < repeat_cycle) {
                count = end - i;

                break;
            } else {
                count = repeat_cycle;
            }

            if (repeat_samples_nr > 0) {
                new_channel.insert(new_channel.end(), i, i + count);

                int rest;
                for (rest = repeat_samples_nr; rest > count; rest -= count) {
                    new_channel.insert(new_channel.end(), i, i + count);
                }
                if (rest) {
                    new_channel.insert(new_channel.end(), i, i + rest);
                }
            } else if (count + repeat_samples_nr > 0) {
                new_channel.insert(
                    new_channel.end(),
                    i,
                    i + count + repeat_samples_nr);
            }
        }
        result.channels.push_back(std::move(new_channel));
    }

    return result;
}

} // namespace niu2x::media