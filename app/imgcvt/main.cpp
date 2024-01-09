#include <niu2x/fs.h>
#include <niu2x/image.h>
#include <niu2x/arg_parser.h>
#include <niu2x/logger.h>
#include <niu2x/string_utils.h>
#include <niu2x/math.h>
#include <niu2x/bite.h>

using namespace niu2x;
using Path = fs::AbsPath;

struct Config {
    Maybe<math::IntRect> crop_region;
};

static void set_store_format(image::Image* img, const Path& output_path)
{
    auto ext = output_path.extension();
    default_logger << "set_store_format: " << ext << "\n";

    string_utils::lower(&ext);

    if (ext == ".png") {
        img->set_store_format(image::FileFormat::PNG);
    }

    else if (ext == ".jpg" || ext == ".jpeg") {
        img->set_store_format(image::FileFormat::JPG);
    }
}

static void
imgcvt(const Path& input_path, const Path& output_path, const Config& config)
{
    image::Image img;
    default_logger << "load_from_file: " << input_path << "\n";
    img.load_from_file(input_path);

    if (config.crop_region) {
        img = img.crop(*config.crop_region);
    }

    set_store_format(&img, output_path);
    img.store_to_file(output_path);
}

static void parse_config(Config* config, const ArgParser& arg_parser)
{
    if (arg_parser.exists("crop")) {
        auto crop = arg_parser.opt_string("crop");
        auto fields = string_utils::split(crop, ',');
        if (fields.size() != 4) {
            throw_runtime_err("--crop should be 4 integers");
        }

        int left = std::stoi(fields[0]);
        int top = std::stoi(fields[1]);
        int width = std::stoi(fields[2]);
        int height = std::stoi(fields[3]);

        config->crop_region = math::IntRect(left, top, width, height);
    }
}

class AppEntry : public bite::Entry {
public:
    AppEntry()
    : bite::Entry("imgcvt")
    {
    }

    void init_options(ArgParser* ap) const override
    {
        using AT = ArgParser::ArgType;
        ap->add_option("i,input", AT::STRING, "input image path", true);
        ap->add_option("o,output", AT::STRING, "output image path", true);
        ap->add_option(
            "crop",
            AT::STRING,
            "crop a region, eg: --crop left,top,width,height",
            false);
        ap->set_positional_args({ "input", "output" });
    }

    int run(const ArgParser& ap) override
    {

        Path input_path = ap.opt_string("input");
        Path output_path = ap.opt_string("output");

        Config config;
        parse_config(&config, ap);

        imgcvt(input_path, output_path, config);

        return 0;
    }

private:
};

int main(int argc, const char* argv[])
{
    AppEntry app;
    return app.main(argc, argv);
}