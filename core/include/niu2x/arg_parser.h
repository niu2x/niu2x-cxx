#ifndef NIU2X_ARG_PARSER_H
#define NIU2X_ARG_PARSER_H

#include <niu2x/std_alias.h>
#include <niu2x/exception.h>

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
        const String& full_opt_name,
        ArgType type,
        const String& desc,
        bool required = false);

    void set_default_value(const String& opt_name, const ArgValue& defval);

    void set_positional_args(const ArgNameList& arg_names);

    void show_help() const;

    String opt_string(const String& opt_name) const
    {
        return opt<String>(opt_name);
    }

    bool opt_boolean(const String& opt_name) const
    {
        return opt<bool>(opt_name);
    }

    template <class T>
    T opt(const String& opt_name) const
    {
        auto& value_key = args_.at(opt_name).value_key;

        if (values_.contains(value_key))
            return get<T>(values_.at(value_key));

        if (default_values_.contains(value_key))
            return get<T>(default_values_.at(value_key));

        throw_runtime_err("no value for argument: " + opt_name);

        return T();
    }

    bool exists(const String& opt_name) const;

    void set_ignore_unknown_option(bool b) { ignore_unknown_args_ = b; }

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
    ArgValueDict default_values_;
    ArgNameList positional_arg_names_;

    bool ignore_unknown_args_ = false;

    void check_required_args_got_value();
};

static_assert(type_pred::is_movable<ArgParser>);

} // namespace niu2x

#endif