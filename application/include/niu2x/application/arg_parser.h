#ifndef NIU2X_APPLICATION_ARG_PARSER_H
#define NIU2X_APPLICATION_ARG_PARSER_H

#include <niu2x/type.h>

namespace niu2x::app {

class ArgParser : private Noncopyable {
public:
    enum ArgType {
        INT,
        BOOL,
        STRING,
    };

    ArgParser(const String& program_name, const String& desc);
    ~ArgParser();

    void add_option(const String& opt, const String& desc, ArgType arg_type,
        const char* defval = nullptr);

    void parse_positional(const String& opt_name);
    void parse_positional(const InitializerList<String>& opt_name_list);

    void parse(int argc, const char* argv[]);
    String help() const;

    String opt_string(const String& opt_name) const;

    int count(const String& opt_name) const;
    Vector<String> unmatched() const;

private:
    class IMP;
    IMP* pimp_;
};

} // namespace niu2x::app

#endif
