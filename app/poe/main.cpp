#include <niu2x/type.h>
#include <niu2x/gfx.h>

using namespace niu2x;

int main()
{
    auto window = gfx::WindowFactory::get()->create_window();
    window->set_full_screen(true);
    window->set_full_screen(false);
    window->poll();
    return 0;
}