#ifndef NIU2X_ARG_PARSER_H
#define NIU2X_ARG_PARSER_H

#include <niu2x/std_alias.h>

namespace niu2x {

class ArgParser {
public:
    enum class ArgType {
        INTEGER,
        NUMBER,
        STRING,
        BOOLEAN,
    };

    using ArgValue = Variant<int, double, String, bool>;

    using ArgNameList = Vector<String>;

    ArgParser(const String& app_name);
    void parse(int argc, const char* argv[]);
    void add_option(
        const String& opt_name,
        ArgType type,
        const String& desc,
        bool required = false);

    void set_positional_args(const ArgNameList& arg_names);

private:
    String app_name_;

    struct Argument {
        String name;
        String desc;
        ArgType type;
        bool required;
        String value_key;
    };
    using ArgumentDict = HashMap<String, Argument>;
    using ArgValueDict = HashMap<String, ArgValue>;

    ArgumentDict args_;
    ArgValueDict values_;
    ArgNameList positional_arg_names_;
};

static_assert(type_pred::is_movable<ArgParser>);

} // namespace niu2x

#endif