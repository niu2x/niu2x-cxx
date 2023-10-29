#ifndef NIU2X_GFX_GLFW_WINDOW_H
#define NIU2X_GFX_GLFW_WINDOW_H

#include <niu2x/noncopyable.h>
#include <niu2x/gfx/window.h>
#include "glad/glad.h"
#include <GLFW/glfw3.h>

namespace niu2x::gfx {

class GLFW_Window : public Window, private Noncopyable {
public:
    GLFW_Window();
    ~GLFW_Window();
    void set_window_size(IntSize window_size) override;
    void poll() override;
    void set_full_screen(bool b) override;

private:
    GLFWwindow* native_win_;

    IntSize window_size_cache_;

    void cache_window_size();
};

} // namespace niu2x::gfx

#endif