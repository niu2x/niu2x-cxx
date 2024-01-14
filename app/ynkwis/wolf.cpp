#include <niu2x/uv.h>
#include <niu2x/bite.h>
#include <niu2x/noncopyable.h>
#include <niu2x/logger.h>

using namespace niu2x;

class WolfClient : private Noncopyable {
public:
    WolfClient(UniquePtr<uv::TCP> tcp)
    : tcp_(move(tcp))
    {
    }

    ~WolfClient() { }

    bool is_done() const { return true; }

private:
    UniquePtr<uv::TCP> tcp_;
};

class WolfEntry : public bite::Entry {
public:
    WolfEntry()
    : Entry("ynkwis-wolf")
    {
    }

    ~WolfEntry() { }

    void init_options(ArgParser* arg_parser) const override { }

    int run(const ArgParser& arg_parser) override
    {
        uv::TCP listen_sock(&uv_loop_);
        listen_sock.bind("127.0.0.1", 8082);
        listen_sock.listen([this](auto client) {
            clients_.push_back(make_unique<WolfClient>(move(client)));
        });

        uv::Timer timer_for_check_clients(
            &uv_loop_,
            [this]() {
                logger << "timer_for_check_clients\n";
                check_dead_clients();
            },
            5);

        timer_for_check_clients.start();

        uv_loop_.run_loop();
        return 0;
    }

private:
    uv::Loop uv_loop_;
    Vector<UniquePtr<WolfClient>> clients_;

    void check_dead_clients()
    {
        clients_.erase(
            std::remove_if(
                clients_.begin(),
                clients_.end(),
                [](auto& x) { return x->is_done(); }),
            clients_.end());
    }
};

int main(int argc, const char* argv[])
{
    WolfEntry app;
    return app.main(argc, argv);

    // uv::TCP listen_sock(&uv_loop);
    // return 0;
}