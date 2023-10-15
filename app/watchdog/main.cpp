#include <iostream>
#include <niu2x/lua.h>
#include <niu2x/app.h>

using namespace niu2x;

int main(int argc, const char* argv[])
{
    app::ArgParser arg_parser("watchdog", "watchdog's desc");
    arg_parser.add_option("h,help", "show help info", false);
    arg_parser.parse(argc, argv);
    if (arg_parser.count("help")) {
        std::cout << arg_parser.help() << std::endl;
    }

    // arg_parser.add_option("");
    return 0;
}