#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/complex.h>
#include <niu2x/std_alias.h>
#include <niu2x/media.h>
#include <niu2x/filesystem.h>
#include <niu2x/stream.h>

namespace py = pybind11;
namespace n2 = niu2x;

namespace media {

using SoundData = n2::media::SoundData;

SoundData wav_decode(const n2::String& path)
{
    n2::fs::File wav_file(path);
    n2::stream::FileByteReadStream wav_s(wav_file);

    n2::media::WavCodec wav_codec;
    return wav_codec.decode(&wav_s);
}

void wav_encode(const SoundData& sd, const n2::String& path)
{
    n2::fs::File wav_file(path);
    n2::stream::FileByteWriteStream wav_s(wav_file);

    n2::media::WavCodec wav_codec;
    return wav_codec.encode(sd, &wav_s);
}

} // namespace media

PYBIND11_MODULE(niupy, m)
{
    m.doc() = "niupy"; // optional module docstring

    auto media = m.def_submodule("media", "This is media submodule");
    media.def("wav_decode", &media::wav_decode);
    media.def("wav_encode", &media::wav_encode);

    py::class_<media::SoundData>(media, "SoundData")
        .def(py::init<>())
        .def_readwrite("sample_bits", &media::SoundData::sample_bits)
        .def_readwrite("channels", &media::SoundData::channels)
        .def_readwrite("sample_frequency", &media::SoundData::sample_frequency);
}
