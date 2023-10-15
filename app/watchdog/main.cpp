#include <iostream>
#include <niu2x/lua.h>
#include <niu2x/app.h>

using namespace niu2x;

static int start() { return 0; }
static int stop() { return 0; }
static int status() { return 0; }

int main(int argc, const char* argv[])
{
    app::ArgParser arg_parser("watchdog", "watchdog's desc");
    using ArgType = app::ArgParser::ArgType;
    arg_parser.add_option("h,help", "show help info", ArgType::BOOL, "false");
    arg_parser.add_option("c,config", "config file", ArgType::STRING);
    arg_parser.add_option(
        "operation", "start/stop/status", ArgType::STRING, "status");
    arg_parser.parse_positional("operation");

    arg_parser.parse(argc, argv);
    if (arg_parser.count("help")) {
        std::cout << arg_parser.help() << std::endl;
        return 1;
    }

    auto operation = arg_parser.opt_string("operation");
    if (operation == "status") {
        return status();
    } else if (operation == "start") {
        if (!arg_parser.count("config")) {
            std::cerr << "please give me a config" << std::endl;
        }
        return start();
    } else if (operation == "stop") {
        return stop();
    } else {
        std::cout << arg_parser.help() << std::endl;
        return 1;
    }
}