#include <niu2x/fs.h>
#include <niu2x/image.h>
#include <niu2x/arg_parser.h>
#include <niu2x/logger.h>
#include <niu2x/string_utils.h>

using namespace niu2x;
using Path = fs::AbsPath;

static ArgParser create_arg_parser()
{
    ArgParser arg_parser("imgcvt");
    using AT = ArgParser::ArgType;

    arg_parser.add_option("i,input", AT::STRING, "input image path", true);
    arg_parser.add_option("o,output", AT::STRING, "output image path", true);

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

static void imgcvt(const Path& input_path, const Path& output_path)
{
    image::Image img;
    default_logger << "load_from_file: " << input_path << "\n";
    img.load_from_file(input_path);

    set_store_format(&img, output_path);
    img.store_to_file(output_path);
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

    imgcvt(input_path, output_path);
    return 0;
}