#include <niu2x/media/type.h>

namespace niu2x::media {

double Sound_duration(SoundData* self)
{
    double samples_nr = self->samples.size();
    double duration = samples_nr / self->sample_frequency;
    return duration;
}

} // namespace niu2x::media