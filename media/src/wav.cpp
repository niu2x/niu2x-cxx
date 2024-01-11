#include <niu2x/media/codec/wav.h>
#include <niu2x/unused.h>
#include <niu2x/bit.h>

#define MONO   (0x01)
#define STEREO (0x02)

namespace niu2x::media {

template <class T>
void read_audio_data_IMP(
    SoundData* sound,
    ByteReadStream* input,
    NR size,
    T max_sample_value)
{
    for (Index i = 0; i < size; i++) {
        T x = input->read_value<T>();
        x = le_to_host(x);
        double value = ((double)x) / max_sample_value;
        sound->samples.push_back(value);
    }
}

static void read_audio_data(
    SoundData* sound,
    ByteReadStream* input,
    int bits_per_sample,
    int size_of_data_chunk)
{
    switch (bits_per_sample) {
        case 16: {
            read_audio_data_IMP<int16_t>(
                sound,
                input,
                size_of_data_chunk / 2,
                32767);
            break;
        }
        default: {
            throw_runtime_err(
                "dont't support bits_per_sample: "
                + to_string(bits_per_sample));
        }
    }
}

void WavCodec::encode(const SoundData&, ByteWriteStream* output) const
{
    unused(output);
}

SoundData WavCodec::decode(ByteReadStream* input) const
{
    char riff_desc[4];
    input->read_char(riff_desc, 4);

    if (!std::equal(riff_desc, riff_desc + 4, "RIFF")) {
        throw_runtime_err("riff_desc is not RIFF");
    }

    NR size_of_file = le_to_host(input->read_u32());
    unused(size_of_file);

    char wav_desc[4];
    input->read_char(wav_desc, 4);

    if (!std::equal(wav_desc, wav_desc + 4, "WAVE")) {
        throw_runtime_err("wav_desc is not WAVE");
    }

    char fmt_desc[4];
    input->read_char(fmt_desc, 4);

    if (!std::equal(fmt_desc, fmt_desc + 4, "fmt ")) {
        throw_runtime_err("fmt_desc is not fmt: " + String(fmt_desc));
    }

#define READ(name, bits)                                                       \
    auto name = le_to_host(input->NIU2X_PP_CAT(read_u, bits)());               \
    unused(name);
    // default_logger << NIU2X_PP_STR(name) ": " << name << "\n";

    READ(size_of_section_chunk, 32);
    READ(wav_type_format, 16);
    READ(mono_stereo_flag, 16);
    READ(sample_frequency, 32);
    READ(bytes_per_sec, 32);
    READ(block_alignment, 16);
    READ(bits_per_sample, 16);

    if (mono_stereo_flag != MONO) {
        throw_runtime_err(
            "dont't support mono_stereo_flag: " + to_string(mono_stereo_flag));
    }

    if (sample_frequency * (bits_per_sample >> 3) != bytes_per_sec) {
        throw_runtime_err(
            "sample_frequency * bits_per_sample / 8 != bytes_per_sec");
    }

    char data_desc[4];
    input->read_char(data_desc, 4);

    if (!std::equal(data_desc, data_desc + 4, "data")) {
        throw_runtime_err("data_desc is not fmt: " + String(data_desc));
    }
    READ(size_of_data_chunk, 32);

    SoundData sound;
    sound.sample_frequency = sample_frequency;
    sound.sample_bits = bits_per_sample;

    read_audio_data(&sound, input, bits_per_sample, size_of_data_chunk);

    return sound;
}

} // namespace niu2x::media