#include <niu2x/arg_parser.h>
#include <niu2x/unused.h>
#include <niu2x/string_utils.h>
#include <niu2x/logger.h>
#include <niu2x/convention.h>
#include <niu2x/string_utils.h>
#include <string>

namespace niu2x {

ArgParser::ArgParser(const String& app_name)
: app_name_(app_name)
{
    // add_option("h,help", ArgType::BOOLEAN, "show help", false);
    // set_default_value("help", false);
}

void ArgParser::parse(int argc, const char* argv[])
{
    Index positional_index = 0;
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
            if (positional_index < positional_arg_names_.size()) {
                name = positional_arg_names_[positional_index++];
                value = argv[i];
                got_value = true;
            } else {
                throw_runtime_err("unsupport positional argument");
            }
        }

        if (args_.find(name) == args_.end()) {
            throw_runtime_err("unsupport option " + name);
        }

        auto argument = args_.at(name);
        bool need_value = argument.type != ArgType::BOOLEAN;

        if (need_value && (!got_value)) {
            if (i + 1 < argc) {
                value = argv[++i];
                got_value = true;
            } else {
                throw_runtime_err("no value for " + name);
            }
        }

        // default_logger << "name: " << name << "\n";
        // default_logger << "value: " << value << "\n";
        // default_logger << "got_value: " << got_value << "\n";
        //

        switch (argument.type) {
            case ArgType::INTEGER: {
                values_[argument.value_key] = std::stoi(value);
                break;
            }
            case ArgType::NUMBER: {
                values_[argument.value_key] = std::stod(value);
                break;
            }
            case ArgType::BOOLEAN: {
                if (got_value) {
                    string_utils::lower(&value);
                    values_[argument.value_key]
                        = value != "false" && value != "off";
                } else {
                    values_[argument.value_key] = true;
                }
                break;
            }
            case ArgType::STRING: {
                values_[argument.value_key] = value;
                break;
            }
        }
    }

    // if (opt_boolean("help")) {
    // throw_runtime_err("show help");
    // }

    check_required_args_got_value();
}

void ArgParser::check_required_args_got_value()
{
    for (auto& x : args_) {
        if (x.second.required) {
            if (!values_.contains(x.second.value_key)) {
                throw_runtime_err(
                    "argument " + x.second.value_key + " required a value");
            }
        }
    }
}

void ArgParser::show_help() const
{
    printf("Usage: %s [options]\n", app_name_.c_str());
    printf(" The options are:\n");

    HashMap<String, Argument> options;
    for (auto& x : args_) {
        options[x.second.value_key] = x.second;
    }

    for (auto& x : options) {
        printf("  %-32s%s\n", x.first.c_str(), x.second.desc.c_str());
    }
}

void ArgParser::set_default_value(
    const String& opt_name,
    const ArgValue& defval)
{
    auto& value_key = args_.at(opt_name).value_key;
    default_values_[value_key] = defval;
}

void ArgParser::add_option(
    const String& opt_name,
    ArgType type,
    const String& desc,
    bool required)
{
    auto fields = string_utils::split(opt_name, ',');
    for (auto& name : fields) {
        args_[name] = {
            .name = name,
            .desc = desc,
            .type = type,
            .required = required,
            .value_key = opt_name,
        };
    }
}
void ArgParser::set_positional_args(const ArgNameList& arg_names)
{
    positional_arg_names_ = arg_names;
}

} // namespace niu2x