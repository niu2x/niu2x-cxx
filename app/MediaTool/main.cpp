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
        ap->add_option(
            "dump-samples",
            AT::BOOLEAN,
            "dump sound samples",
            false);
        ap->set_positional_args({ "input" });
        ap->set_default_value("dump-samples", false);
    }

    int run(const ArgParser& ap) override
    {
        media::WavCodec codec;
        fs::File file(ap.opt_string("input"));
        stream::FileByteReadStream input_s(file);
        auto sound_data = codec.decode(&input_s);

        if (ap.opt_boolean("dump-samples")) {

            for (auto& x : sound_data.samples) {
                std::cout << x << std::endl;
            }

        } else {

            std::cout << "sound sample frequency: "
                      << sound_data.sample_frequency << std::endl;
            std::cout << "sound sample bits: " << sound_data.sample_bits
                      << std::endl;
            std::cout << "sound duration: "
                      << media::Sound_duration(&sound_data) << std::endl;
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