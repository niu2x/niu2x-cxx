#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <iostream>
#include <niu2x/lua.h>
#include <niu2x/app.h>
#include <niu2x/fs.h>
#include <niu2x/stream.h>
#include <niu2x/uv.h>

using namespace niu2x;

struct Status {
    bool running = false;
};

struct Config {
    bool daemon = false;
};

static const fs::Path pid_path = "/run/niu2x/watchdog.pid";
static Config config;

static void Status_show(Status* self)
{
    std::cout << "running: " << to_string(self->running) << std::endl;
}

static void do_job() { }

static void job()
{
    uv::Loop loop;
    auto timer = loop.create_timer();
    auto signal = loop.create_signal();
    loop.timer_start(timer, 1000, 1000, []() { do_job(); });
    loop.signal_start(signal, SIGINT, [&loop, timer, signal](int signum) {
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
        auto r = fork();
        if (r == -1) {
            printf("fork fail\n");
            return 1;
        } else if (r == 0) {

            auto r1 = fork();
            if (r1 == -1) {
                printf("fork fail\n");
                return 1;
            } else if (r1 == 0) {
                {
                    fs::File pid_file(pid_path);
                    pid_file.parent().ensure_dirs();
                    stream::FileWriteStream pid_os(pid_file);
                    String pid = to_string(getpid());
                    pid_os.write(pid.c_str(), pid.size());
                }
                setsid();
                close(0);
                close(1);
                close(2);
                job();
            }
        } else {
            int wstatus = 0;
            waitpid(r, &wstatus, 0);
        }
    } else {
        job();
    }

    return 0;
}

static int stop()
{

    if (fs::exists(pid_path)) {
        fs::File pid_file(pid_path);

        stream::BufferWriteStream tmp;
        stream::FileReadStream pid_in(pid_file);
        pipe(&pid_in, &tmp);
        String pid_sz = tmp.buffer().str();
        pid_t pid = atoll(pid_sz.c_str());
        if (!kill(pid, SIGINT)) {
            fs::remove(pid_path);
        } else if (EPERM == errno) {
            printf("no permission\n");
            return 1;
        }
    }
    return 0;
}

static int status()
{
    Status status;
    if (fs::exists(pid_path)) {
        fs::File pid_file(pid_path);

        stream::BufferWriteStream tmp;
        stream::FileReadStream pid_in(pid_file);
        pipe(&pid_in, &tmp);
        String pid_sz = tmp.buffer().str();
        pid_t pid = atoll(pid_sz.c_str());
        if (!kill(pid, 0))
            status.running = true;
        else if (EPERM == errno) {
            printf("no permission\n");
            return 1;
        }
    }

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
            return 1;
        }
        return start();
    } else if (operation == "stop") {
        return stop();
    } else {
        std::cout << arg_parser.help() << std::endl;
        return 1;
    }
}