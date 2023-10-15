#include <signal.h>
#include <iostream>
#include <niu2x/lua.h>
#include <niu2x/app.h>
#include <niu2x/fs.h>
#include <niu2x/uv.h>

using namespace niu2x;

struct Status {
    bool running = false;
};

struct Config {
    bool daemon = false;
};

static const fs::Path pid_file = "/run/niu2x/watchdog.pid";
static Config config;

static void Status_show(Status* self)
{
    std::cout << "running: " << to_string(self->running) << std::endl;
}

static void job()
{
    uv::Loop loop;
    auto timer = loop.create_timer();
    auto signal = loop.create_signal();
    loop.timer_start(timer, 1000, 1000, []() { printf("job\n"); });
    loop.signal_start(signal, SIGINT, [&loop, timer, signal](int signum) {
        printf("ctrl-c\n");
        loop.signal_stop(signal);
        loop.timer_stop(timer);
    });
    loop.run();

    loop.destroy_timer(timer);
    loop.destroy_signal(signal);
    loop.run();

    loop.close();
}

static int start()
{
    if (config.daemon) {

    } else {
        job();
    }
    return 0;
}

static int stop() { return 0; }
static int status()
{
    Status status;
    if (fs::exists(pid_file)) { }
    Status_show(&status);
    return 0;
}

int main(int argc, const char* argv[])
{
    app::ArgParser arg_parser("watchdog", "watchdog's desc");
    using ArgType = app::ArgParser::ArgType;
    arg_parser.add_option("h,help", "show help info", ArgType::BOOL, "false");
    arg_parser.add_option("c,config", "config file", ArgType::STRING);
    arg_parser.add_option("d,daemon", "daemon mode", ArgType::BOOL, "false");
    arg_parser.add_option(
        "operation", "start/stop/status", ArgType::STRING, "status");
    arg_parser.parse_positional("operation");

    arg_parser.parse(argc, argv);
    if (arg_parser.count("help")) {
        std::cout << arg_parser.help() << std::endl;
        return 1;
    }

    if (arg_parser.count("daemon")) {
        config.daemon = true;
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