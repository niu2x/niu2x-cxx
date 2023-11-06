#ifndef NIU2X_GFX_GLFW_WINDOW_H
#define NIU2X_GFX_GLFW_WINDOW_H

#include <niu2x/noncopyable.h>
#include <niu2x/gfx/window.h>
#include "glad/glad.h"
#include <GLFW/glfw3.h>

namespace niu2x::gfx {

class GLFW_Init : private Noncopyable {
public:
    GLFW_Init();
    ~GLFW_Init();
};

class GLFW_Window : public Window, private Noncopyable {
public:
    GLFW_Window();
    ~GLFW_Window();
    void set_window_size(IntSize window_size) override;
    void poll() override;
    void set_full_screen(bool b) override;
    void set_delegate(UniquePtr<Delegate> delegate) override
    {
        delegate_ = move(delegate);
    }
    void on_resize(IntSize window_size);

private:
    GLFWwindow* native_win_;
    IntSize window_size_cache_;
    UniquePtr<Delegate> delegate_;
    GLFW_Init glfw_init_;
    void cache_window_size();
};

class GLFW_WindowWithRenderContext : public GLFW_Window {
public:
    GLFW_WindowWithRenderContext();
    ~GLFW_WindowWithRenderContext();

private:
    GLuint vao_;
};

} // namespace niu2x::gfx

#endif