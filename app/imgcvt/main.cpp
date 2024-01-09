#include <niu2x/fs.h>
#include <niu2x/image.h>
#include <niu2x/arg_parser.h>
#include <niu2x/logger.h>
#include <niu2x/string_utils.h>
#include <niu2x/math.h>

using namespace niu2x;
using Path = fs::AbsPath;

struct Config {
    Maybe<math::IntRect> crop_region;
};

static ArgParser create_arg_parser()
{
    ArgParser arg_parser("imgcvt");
    using AT = ArgParser::ArgType;

    arg_parser.add_option("i,input", AT::STRING, "input image path", true);
    arg_parser.add_option("o,output", AT::STRING, "output image path", true);
    arg_parser.add_option(
        "crop",
        AT::STRING,
        "crop a region, eg: --crop left,top,width,height",
        false);
    arg_parser.set_positional_args({ "input", "output" });
    return arg_parser;
}

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

int main(int argc, const char* argv[])
{
    auto arg_parser = create_arg_parser();
    try {
        arg_parser.parse(argc, argv);
    } catch (Exception& e) {
        std::cerr << e.what() << std::endl << std::endl;
        arg_parser.show_help();
        return 1;
    }

    Path input_path = arg_parser.opt_string("input");
    Path output_path = arg_parser.opt_string("output");

    Config config;
    parse_config(&config, arg_parser);

    imgcvt(input_path, output_path, config);
    return 0;
}