#include <niu2x/bite/entry.h>

namespace niu2x::bite {
Entry::~Entry() { }

Entry::Entry(const String& app_name)
: arg_parser_(app_name)
, usage_version_parser_(app_name)
, app_name_(app_name)
{
}

int Entry::main(int argc, const char* argv[])
{
    using AT = ArgParser::ArgType;
    usage_version_parser_
        .add_option("v,version", AT::BOOLEAN, "show version", false);
    usage_version_parser_
        .add_option("h,help", AT::BOOLEAN, "show usage", false);
    usage_version_parser_.set_ignore_unknown_option(true);
    init_options(&arg_parser_);

    setup();

    int status = 255;

    usage_version_parser_.parse(argc, argv);
    if (usage_version_parser_.exists("help")) {
        status = show_usage();
    } else if (usage_version_parser_.exists("version")) {
        status = show_version();
    } else {
        try {
            arg_parser_.parse(argc, argv);
            status = run(arg_parser_);
        } catch (Exception& e) {
            std::cerr << e.what() << std::endl;
        }
    }

    cleanup();
    return status;
}

} // namespace niu2x::bite