#ifndef NIU2X_UV_PROCESS_H
#define NIU2X_UV_PROCESS_H

#include <niu2x/noncopyable.h>
#include <niu2x/type.h>
#include <niu2x/uv/exception.h>

namespace niu2x::uv {

class Loop;

class Process : private Noncopyable {
public:
    using ExitCallback = Function<void(int64_t exit_status)>;

    struct Options {
        String file;
        Vector<String> args;
    };

    Process(
        Loop* loop,
        const Options& options,
        ExitCallback callback,
        bool detach = false);
    ~Process();

    void* native() const { return native_.data(); }
    void join();
    bool joinable() const { return joinable_; }

private:
    MallocHandle native_;
    ExitCallback callback_;
    Loop* loop_;
    bool joinable_;
    bool exited_ = false;
    static void uv_callback(void* req, int64_t exit_status, int term_signal);
};

} // namespace niu2x::uv

#endif