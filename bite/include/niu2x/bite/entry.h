#ifndef NIU2X_BITE_ENTRY_H
#define NIU2X_BITE_ENTRY_H

#include <niu2x/noncopyable.h>
#include <niu2x/preprocess.h>
#include <niu2x/unused.h>
#include <niu2x/std_alias.h>
#include <niu2x/arg_parser.h>

namespace niu2x::bite {

class Entry : private Noncopyable {
public:
    // NIU2X_PP_NO_MOVABLE(Entry);
    Entry(const String& app_name);

    virtual ~Entry();

    virtual int show_version() const
    {
        std::cout << app_name_ << ": version info" << std::endl;
        return 1;
    }
    virtual int show_usage() const
    {
        // std::cout << app_name_ << ": usage info" << std::endl;
        arg_parser_.show_help();
        return 1;
    }
    virtual void init_options(ArgParser* arg_parser) const
    {
        unused(arg_parser);
    }
    virtual int run(const ArgParser& arg_parser)
    {
        unused(arg_parser);
        return 0;
    }

    virtual void setup() { }
    virtual void cleanup() { }

    int main(int argc, const char* argv[]);

    const String& app_name() const { return app_name_; }

private:
    ArgParser arg_parser_;
    ArgParser usage_version_parser_;
    String app_name_;
};

} // namespace niu2x::bite

#endif
