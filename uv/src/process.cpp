#include <niu2x/uv/process.h>
#include <niu2x/uv/loop.h>
#include <niu2x/unused.h>
#include "uv.h"
#include "helper.h"

struct NativeProcess {
    uv_process_t process;
    uv_process_options_t options;
};

#define native_process() (reinterpret_cast<NativeProcess*>(native_.data()))

namespace niu2x::uv {
Process::Process(
    Loop* loop,
    const Options& options,
    ExitCallback callback,
    bool detach)
: native_(sizeof(NativeProcess))
, callback_(callback)
, loop_(loop)
, joinable_(!detach)
// , options_(options)
{
    auto np = native_process();
    memset(np, 0, sizeof(NativeProcess));

    char* args[256] = { nullptr };
    if (options.args.size() > 255) {
        throw_runtime_err("Process too many args");
    }

    for (Index i = 0; i < options.args.size(); i++) {
        args[i] = (char*)options.args[i].c_str();
    }

    using CALLBACK_T = void (*)(uv_process_t*, int64_t, int);

    np->options.exit_cb = (CALLBACK_T)uv_callback;
    np->options.file = options.file.c_str();
    np->options.args = args;

    if (detach)
        np->options.flags = UV_PROCESS_DETACHED;

    auto uv_loop = reinterpret_cast<uv_loop_t*>(loop->native());

    np->process.data = this;

    int r;
    if ((r = uv_spawn(uv_loop, &(np->process), &(np->options)))) {
        throw_runtime_err("Process spawn fail");
    } else {
        // fprintf(stderr, "Launched process with ID %d\n", child_req.pid);
    }
}
Process::~Process()
{
    if (joinable()) {
        join();
    }
    auto uv_process = UV_TYPE(uv_process_t*, native_.data());
    UV_ENSURE_CLOSE(uv_process, loop_);
}

void Process::uv_callback(void* req, int64_t exit_status, int term_signal)
{
    unused(term_signal);
    auto uv_process = UV_TYPE(uv_process_t*, req);
    auto process = reinterpret_cast<Process*>(uv_process->data);
    process->callback_(exit_status);
    process->exited_ = true;
}

void Process::join()
{
    joinable_ = false;
    do {

        loop_->run_once();
    } while (!exited_);
}

} // namespace niu2x::uv