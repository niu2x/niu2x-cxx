#ifndef NIU2X_APPLICATION_ARG_PARSER_H
#define NIU2X_APPLICATION_ARG_PARSER_H

#include <niu2x/type.h>

namespace niu2x::app {

class ArgParser : private Noncopyable {
public:
    ArgParser(const String& program_name, const String& desc);
    ~ArgParser();
    void add_option(const String& opt, const String& desc, bool defval = false);
    void add_option(const String& opt, const String& desc, int defval = 0);
    void parse(int argc, const char* argv[]);
    String help() const;

    int count(const String& opt_name) const;
    Vector<String> unmatched() const;

private:
    class IMP;
    IMP* pimp_;
};

} // namespace niu2x::app

#endif
