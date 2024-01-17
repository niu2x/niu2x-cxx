#include <niu2x/fs.h>
#include <niu2x/image.h>
#include <niu2x/arg_parser.h>
#include <niu2x/logger.h>
#include <niu2x/string_utils.h>
#include <niu2x/math.h>
#include <niu2x/bite.h>
#include <niu2x/media.h>
#include <niu2x/stream.h>

using namespace niu2x;
using Path = fs::AbsPath;

class AppEntry : public bite::Entry {
public:
    AppEntry()
    : bite::Entry("MediaTool")
    {
    }

    void init_options(ArgParser* ap) const override
    {
        using AT = ArgParser::ArgType;
        ap->add_option("i,input", AT::STRING, "input media file path", true);
        ap->add_option("o,output", AT::STRING, "input media file path", false);
        ap->add_option("change-speed", AT::NUMBER, "change speed", false);
        ap->add_option("verbose", AT::BOOLEAN, "verbose", false);
        ap->add_option(
            "crop",
            AT::STRING,
            "crop sound by time (seconds), eg: --crop 9,2",
            false);
        ap->add_option(
            "dump-samples",
            AT::BOOLEAN,
            "dump sound samples",
            false);
        ap->set_positional_args({ "input", "output" });
        ap->set_default_value("dump-samples", false);
        ap->set_default_value("verbose", false);
    }

    int run(const ArgParser& ap) override
    {
        media::WavCodec codec;
        fs::File file(ap.opt_string("input"));
        stream::FileByteReadStream input_s(file);
        auto sound_data = codec.decode(&input_s);
        bool verbose = ap.opt_boolean("verbose");

        if (verbose)
            std::cout << "input audio file: " << file.path() << std::endl;

        if (ap.exists("crop")) {
            auto crop_sz = ap.opt_string("crop");
            auto fields = string_utils::split(crop_sz, ',');
            double start = 0, duration = -1;
            start = std::stod(fields[0]);
            if (fields.size() >= 2) {
                duration = std::stod(fields[1]);
            }

            if (verbose)
                std::cout << "input audio crop: " << start << "," << duration
                          << std::endl;

            sound_data = Sound_crop(sound_data, start, duration);
        }

        if (ap.exists("change-speed")) {
            double speed_scale = ap.opt_number("change-speed");
            if (verbose)
                std::cout << "change-speed: x" << speed_scale << "\n";

            sound_data = Sound_change_speed(sound_data, speed_scale);
        }

        if (ap.opt_boolean("dump-samples")) {
            auto channels_nr = sound_data.channels.size();
            for (Index cindex = 0; cindex < channels_nr; cindex++) {
                std::cout << "channel " << cindex << std::endl;
                for (auto& x : sound_data.channels[0]) {
                    std::cout << x << std::endl;
                }
            }

        } else {

            if (ap.exists("output")) {
                fs::File file(ap.opt_string("output"));
                stream::FileByteWriteStream out_s(file);
                codec.encode(sound_data, &out_s);
            }

            std::cout << "output sound sample frequency: "
                      << sound_data.sample_frequency << std::endl;
            std::cout << "output sound sample bits: " << sound_data.sample_bits
                      << std::endl;
            std::cout << "output sound duration: "
                      << media::Sound_duration(sound_data) << std::endl;
        }

        return 0;
    }

private:
};

int main(int argc, const char* argv[])
{
    AppEntry app;
    return app.main(argc, argv);
}