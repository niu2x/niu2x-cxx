#include <niu2x/fs.h>
#include <niu2x/arg_parser.h>

using namespace niu2x;

static ArgParser create_arg_parser()
{
    ArgParser arg_parser("imgcvt");
    arg_parser
        .add_option("h,help", ArgParser::ArgType::BOOLEAN, "show help", false);
    return arg_parser;
}

int main(int argc, const char* argv[])
{
    auto arg_parser = create_arg_parser();
    arg_parser.parse(argc, argv);
    return 0;
}