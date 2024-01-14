#include <niu2x/uv.h>
#include <niu2x/bite.h>

using namespace niu2x;

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
        listen_sock.listen([](auto client) {

        });
        uv_loop_.run_loop();
        return 0;
    }

private:
    uv::Loop uv_loop_;
};

int main(int argc, const char* argv[])
{
    WolfEntry app;
    return app.main(argc, argv);

    // uv::TCP listen_sock(&uv_loop);
    // return 0;
}