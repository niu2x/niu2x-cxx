#include <niu2x/singleton.h>
#include <niu2x/type/std_alias.h>
#include <niu2x/gfx/window.h>

namespace niu2x::gfx {

class WindowFactory : public Singleton<WindowFactory> {
public:
    WindowFactory() { }
    UniquePtr<Window> create_window();
};

} // namespace niu2x::gfx