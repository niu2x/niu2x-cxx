#include <niu2x/application/arg_parser.h>
#include "cxxopts.hpp"

namespace niu2x::app {

class ArgParser::IMP {
public:
    IMP(const String& program_name, const String& desc)
    : opts_(program_name, desc)
    {
        opts_.show_positional_help();
    }

    template <class ArgType>
    void add_option(const String& opt, const String& desc, const char* defval)
    {
        auto value = cxxopts::value<ArgType>();
        if (defval) {
            value->default_value(defval);
        }
        opts_.add_options()(opt, desc, value);
    }

    void parse(int argc, const char* argv[])
    {
        arguments_ = opts_.parse(argc, argv);
    }

    String help() const { return opts_.help(); }

    int count(const String& opt_name) const
    {
        return arguments_.count(opt_name);
    }

    void parse_positional(const String& opt_name)
    {
        opts_.parse_positional(opt_name);
        opts_.positional_help(opt_name);
    }
    void parse_positional(const InitializerList<String>& opt_name_list)
    {
        opts_.parse_positional(opt_name_list);
        StringBuf sb;
        for (auto& opt_name : opt_name_list) {
            sb << opt_name << " ";
        }
        opts_.positional_help(sb.str());
    }

    String opt_string(const String& opt_name) const
    {
        return arguments_[opt_name].as<String>();
    }

    Vector<String> unmatched() const { return arguments_.unmatched(); }

private:
    cxxopts::Options opts_;
    cxxopts::ParseResult arguments_;
};

ArgParser::ArgParser(const String& program_name, const String& desc)
: pimp_(new IMP(program_name, desc))
{
}
ArgParser::~ArgParser() { delete pimp_; }

void ArgParser::add_option(
    const String& opt, const String& desc, ArgType arg_type, const char* defval)
{
    switch (arg_type) {
        case ArgType::INT: {
            pimp_->add_option<int>(opt, desc, defval);
            break;
        }
        case ArgType::BOOL: {
            pimp_->add_option<bool>(opt, desc, defval);
            break;
        }
        case ArgType::STRING: {
            pimp_->add_option<String>(opt, desc, defval);
            break;
        }
    }
}

void ArgParser::parse(int argc, const char* argv[])
{
    pimp_->parse(argc, argv);
}

String ArgParser::help() const { return pimp_->help(); }

int ArgParser::count(const String& opt_name) const
{
    return pimp_->count(opt_name);
}

Vector<String> ArgParser::unmatched() const { return pimp_->unmatched(); }

void ArgParser::parse_positional(const String& opt_name)
{
    pimp_->parse_positional(opt_name);
}

void ArgParser::parse_positional(const InitializerList<String>& opt_name_list)
{
    pimp_->parse_positional(opt_name_list);
}

String ArgParser::opt_string(const String& opt_name) const
{
    return pimp_->opt_string(opt_name);
}

} // namespace niu2x::app