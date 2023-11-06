#ifndef NIU2X_GFX_WINDOW_H
#define NIU2X_GFX_WINDOW_H

#include <niu2x/unused.h>
#include <niu2x/math/geometry.h>
#include <niu2x/type/std_alias.h>
#include <niu2x/gfx/key_code.h>

namespace niu2x::gfx {

using IntSize = math::IntSize;

class Window {
public:
    class Delegate {
    public:
        virtual ~Delegate() = 0;
        virtual void setup() { }
        virtual void cleanup() { }
        virtual void update(TimeDuration delta) { unused(delta); }
        virtual void on_resize(IntSize window_size) { unused(window_size); }
        virtual void on_key(KeyCode key_code) { unused(key_code); }
    };

    virtual ~Window() = 0;
    virtual void set_window_size(IntSize window_size) = 0;
    virtual void poll() = 0;
    virtual void set_full_screen(bool b) = 0;
    virtual void set_delegate(UniquePtr<Delegate> delegate) = 0;
    virtual void close() = 0;
};

} // namespace niu2x::gfx

#endif