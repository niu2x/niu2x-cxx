#include <niu2x/type.h>
#include <niu2x/gfx.h>

using namespace niu2x;

class PoeWinDelegate : public gfx::Window::Delegate {
public:
    PoeWinDelegate() { }
    ~PoeWinDelegate() { }

    void setup() override { printf("setup\n"); }

    void cleanup() override { printf("cleanup\n"); }
    void update(TimeDuration delta) override { }
};

int main()
{
    auto poe_win_delegate = make_unique<PoeWinDelegate>();
    auto window = gfx::WindowFactory::get()->create_window();
    window->set_delegate(move(poe_win_delegate));
    window->poll();

    return 0;
}