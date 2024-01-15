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
    NR channels_nr,
    T max_sample_value)
{
    for (Index cindex = 0; cindex < channels_nr; cindex++) {
        sound->channels.push_back({});
    }

    for (Index i = 0; i < size; i++) {
        for (Index cindex = 0; cindex < channels_nr; cindex++) {
            T x = input->read_value<T>();
            x = le_to_host(x);
            double value = ((double)x) / max_sample_value;
            sound->channels[cindex].push_back(value);
        }
    }
}

static void read_audio_data(
    SoundData* sound,
    ByteReadStream* input,
    int bits_per_sample,
    NR channels_nr,
    int size_of_data_chunk)
{
    switch (bits_per_sample) {
        case 16: {
            read_audio_data_IMP<int16_t>(
                sound,
                input,
                size_of_data_chunk / 2 / channels_nr,
                channels_nr,
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

#define READ(name, bits)                                                       \
    auto name = le_to_host(input->NIU2X_PP_CAT(read_u, bits)());               \
    unused(name);
// default_logger << NIU2X_PP_STR(name) ": " << name << "\n";

static void read_infos(ByteReadStream* input)
{
    char info_id[5] = { 0 };
    input->read_char(info_id, 4);
    info_id[4] = 0;

    // logger << "info_id:" << info_id << "\n";
    READ(info_length, 32);

    char message[512];
    if (511 < info_length)
        throw_runtime_err("WavCodec: too long info");

    input->read_char(message, info_length);
    message[info_length] = 0;
    // logger << "info:" << message << "\n";
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
    // default_logger << NIU2X_PP_STR(size_of_file) ": " << size_of_file <<
    // "\n";

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

    READ(size_of_section_chunk, 32);
    READ(wav_type_format, 16);
    // READ(mono_stereo_flag, 16);
    READ(channels_nr, 16);
    READ(sample_frequency, 32);
    READ(bytes_per_sec, 32);
    READ(block_alignment, 16);
    READ(bits_per_sample, 16);

    if (sample_frequency * (bits_per_sample >> 3) * channels_nr
        != bytes_per_sec) {
        throw_runtime_err(
            "sample_frequency * bits_per_sample / 8 != bytes_per_sec");
    }

    char chunk_id[4];

    while (true) {
        input->read_char(chunk_id, 4);

        if (std::equal(chunk_id, chunk_id + 4, "LIST")) {
            READ(list_chunk_size, 32);
            char list_type_id[4];
            input->read_char(list_type_id, 4);
            // logger << "list " << list_type_id << "\n";
            read_infos(input);
        } else {
            break;
        }
    }

    if (!std::equal(chunk_id, chunk_id + 4, "data")) {
        throw_runtime_err("chunk_id is not data: " + String(chunk_id));
    }
    READ(size_of_data_chunk, 32);

    SoundData sound;
    sound.sample_frequency = sample_frequency;
    sound.sample_bits = bits_per_sample;

    read_audio_data(
        &sound,
        input,
        bits_per_sample,
        channels_nr,
        size_of_data_chunk);

    return sound;
}

} // namespace niu2x::media