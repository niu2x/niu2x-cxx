#include <niu2x/fs.h>
#include <niu2x/arg_parser.h>

using namespace niu2x;

static ArgParser create_arg_parser()
{
    ArgParser arg_parser("imgcvt");
    using AT = ArgParser::ArgType;

    arg_parser.add_option("i,input", AT::STRING, "input image path", true);
    arg_parser.add_option("o,output", AT::STRING, "output image path", true);

    arg_parser.set_positional_args({ "input", "output" });

    return arg_parser;
}

static void
imgcvt(const fs::AbsPath& input_path, const fs::AbsPath& output_path)
{
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

    fs::AbsPath input_path = arg_parser.opt_string("input");
    fs::AbsPath output_path = arg_parser.opt_string("output");
    imgcvt(input_path, output_path);
    return 0;
}