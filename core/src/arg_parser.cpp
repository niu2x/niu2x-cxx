#include <niu2x/arg_parser.h>
#include <niu2x/unused.h>
#include <niu2x/string_utils.h>
#include <niu2x/logger.h>

namespace niu2x {

ArgParser::ArgParser(const String& app_name)
: app_name_(app_name)
{
}

void ArgParser::parse(int argc, const char* argv[])
{
    for (int i = 1; i < argc; i++) {
        String name;
        String value;
        bool got_value = false;

        char c = argv[i][0];
        if (c == '-') {
            c = argv[i][1];
            if (c == '-') {
                // long option name
                name = &argv[i][2];
            } else {
                // short option name
                name = String(&argv[i][1], 1);

                if (argv[i][2]) {
                    got_value = true;
                    value = &argv[i][2];
                }
            }
        } else {
        }

        auto argument = args_.at(name);
        bool need_value = argument.type != ArgType::BOOLEAN;

        if (need_value && (!got_value)) {
            if (i + 1 < argc) {
                value = argv[++i];
                got_value = true;
            }
        }

        default_logger << "name: " << name << "\n";
        default_logger << "value: " << value << "\n";
        default_logger << "got_value: " << got_value << "\n";
    }
}

void ArgParser::add_option(
    const String& opt_name,
    ArgType type,
    const String& desc,
    bool required)
{
    auto fields = string_utils::split(opt_name, ',');
    for (auto& name : fields) {
        args_[opt_name] = {
            .name = name,
            .desc = desc,
            .type = type,
            .required = required,
        };
    }
}
void ArgParser::set_positional_args(const ArgNameList& arg_names)
{
    positional_arg_names_ = arg_names;
}

} // namespace niu2x