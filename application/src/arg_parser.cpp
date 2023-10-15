#include <niu2x/application/arg_parser.h>
#include "cxxopts.hpp"

namespace niu2x::app {

class ArgParser::IMP {
public:
    IMP(const String& program_name, const String& desc)
    : opts_(program_name, desc)
    {
        opts_.allow_unrecognised_options();
    }

    void add_option(const String& opt, const String& desc, bool defval)
    {
        opts_.add_options()(opt, desc, cxxopts::value<bool>(defval));
    }
    void add_option(const String& opt, const String& desc, int defval)
    {
        opts_.add_options()(opt, desc, cxxopts::value<int>(defval));
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

void ArgParser::add_option(const String& opt, const String& desc, bool defval)
{
    pimp_->add_option(opt, desc, defval);
}
void ArgParser::add_option(const String& opt, const String& desc, int defval)
{
    pimp_->add_option(opt, desc, defval);
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

} // namespace niu2x::app