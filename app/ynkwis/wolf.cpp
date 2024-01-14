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

    int run(const ArgParser& arg_parser) override { return 0; }
};

int main(int argc, const char* argv[])
{

    WolfEntry app;
    return app.main(argc, argv);

    // uv::Loop uv_loop;
    // uv::TCP listen_sock(&uv_loop);
    // listen_sock.bind("127.0.0.1", 8082);
    // uv_loop.run_loop();
    // return 0;
}