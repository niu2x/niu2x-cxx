#ifndef NIU2X_GFX_WINDOW_H
#define NIU2X_GFX_WINDOW_H

#include <niu2x/math/size.h>

namespace niu2x::gfx {

using IntSize = math::IntSize;

class Window {
public:
    virtual ~Window() = 0;
    virtual void set_window_size(IntSize window_size) = 0;
    virtual void poll() = 0;
    virtual void set_full_screen(bool b) = 0;
};

} // namespace niu2x::gfx

#endif