#include "glfw_window.h"

#include <niu2x/type/exception.h>
#include <niu2x/unused.h>
#include "glfw_key_map.h"
#include <niu2x/gfx/draw.h>

namespace niu2x::gfx {

static void error_callback(int error, const char* description)
{
    fprintf(stderr, "Error: %d %s\n", error, description);
}

static void key_callback(
    GLFWwindow* window, int key_code, int scancode, int action, int mods)
{
    unused(window);
    unused(scancode);
    unused(action);
    unused(mods);

    KeyCode key = glfw_key_map[key_code];
    printf("key: %s\n", to_string(key).c_str());
}

static void window_size_callback(GLFWwindow* window, int width, int height)
{
    unused(width);
    unused(height);
    // Get the size of the framebuffer to use this for the viewport
    int fbWidth, fbHeight;
    glfwGetFramebufferSize(window, &fbWidth, &fbHeight);

    // Set the viewport to cover the new framebuffer
    glViewport(0, 0, fbWidth, fbHeight);

    using GLFW_Window = niu2x::gfx::GLFW_Window;

    auto win = reinterpret_cast<GLFW_Window*>(glfwGetWindowUserPointer(window));

    win->on_resize({ width, height });
}

GLFW_Init::GLFW_Init()
{
    if (!glfwInit()) {
        throw_runtime_err("glfw init fail");
    }
}

GLFW_Init::~GLFW_Init() { glfwTerminate(); }

GLFW_WindowWithRenderContext::GLFW_WindowWithRenderContext()
{
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    if (!gladLoadGL()) {
        throw_runtime_err("gladLoadGL failed");
    }

    glGenVertexArrays(1, &vao_);
    glBindVertexArray(vao_);
}

GLFW_WindowWithRenderContext::~GLFW_WindowWithRenderContext()
{
    glDeleteVertexArrays(1, &vao_);
    // TODO release RenderContext
    // TODO destroy delegate_
}

GLFW_Window::GLFW_Window()
{
    glfwSetErrorCallback(error_callback);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);

    native_win_ = glfwCreateWindow(640, 480, "My Title", nullptr, nullptr);
    if (!native_win_) {
        throw_runtime_err("Window or OpenGL context creation failed");
    }

    glfwMakeContextCurrent(native_win_);
    glfwSetKeyCallback(native_win_, key_callback);
    glfwSetWindowSizeCallback(native_win_, window_size_callback);
    glfwSetWindowUserPointer(native_win_, reinterpret_cast<void*>(this));
}

GLFW_Window::~GLFW_Window()
{
    // TODO move this into ~GLFW_WindowWithRenderContext,
    // 保持RAII构造器和析构器的对称
    if (delegate_) {
        delegate_->cleanup();
        delegate_.reset();
    }

    glfwDestroyWindow(native_win_);
}

void GLFW_Window::set_window_size(IntSize window_size)
{
    glfwSetWindowSize(native_win_, window_size.width, window_size.height);
}

void GLFW_Window::on_resize(IntSize window_size)
{
    delegate_->on_resize(window_size);
}

void GLFW_Window::poll()
{
    delegate_->setup();
    auto now = time_now();
    auto prev = now;

    glClearColor(0.5, 0, 0, 1);

    int width, height;
    glfwGetWindowSize(native_win_, &width, &height);
    on_resize({ width, height });

    while (!glfwWindowShouldClose(native_win_)) {
        glfwPollEvents();

        now = time_now();
        delegate_->update(time_diff(prev, now));
        prev = now;

        glfwSwapBuffers(native_win_);
    }
    delegate_->cleanup();
    delegate_.reset();
}

void GLFW_Window::cache_window_size()
{
    int width, height;
    glfwGetWindowSize(native_win_, &width, &height);
    window_size_cache_ = { width, height };
}

void GLFW_Window::set_full_screen(bool b)
{
    if (b) {
        cache_window_size();
        auto monitor = glfwGetPrimaryMonitor();
        const GLFWvidmode* mode = glfwGetVideoMode(monitor);
        glfwSetWindowMonitor(native_win_
        	, monitor
			, 0
			, 0
			, mode->width
			, mode->height
			, mode->refreshRate);

    } else {
        glfwSetWindowMonitor(native_win_
        	, nullptr
        	, 0
        	, 0
        	, window_size_cache_.width
        	, window_size_cache_.height
        	, 0);
    }
}

} // namespace niu2x::gfx