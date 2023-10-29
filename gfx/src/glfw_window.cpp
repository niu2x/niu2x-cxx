#include "glfw_window.h"

#include <niu2x/type/exception.h>
#include <niu2x/unused.h>

namespace niu2x::gfx {

static void error_callback(int error, const char* description)
{
    fprintf(stderr, "Error: %d %s\n", error, description);
}

GLFW_Window::GLFW_Window()
{
    if (!glfwInit()) {
        throw_runtime_err("glfw init fail");
    }
    glfwSetErrorCallback(error_callback);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);

    native_win_ = glfwCreateWindow(640, 480, "My Title", nullptr, nullptr);
    if (!native_win_) {
        throw_runtime_err("Window or OpenGL context creation failed");
    }

    glfwMakeContextCurrent(native_win_);
}

GLFW_Window::~GLFW_Window()
{
    glfwDestroyWindow(native_win_);
    glfwTerminate();
}

void GLFW_Window::set_window_size(IntSize window_size)
{
    glfwSetWindowSize(native_win_, window_size.width, window_size.height);
}

void GLFW_Window::poll()
{
    while (!glfwWindowShouldClose(native_win_)) {
        glfwSwapBuffers(native_win_);
        glfwPollEvents();
    }
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