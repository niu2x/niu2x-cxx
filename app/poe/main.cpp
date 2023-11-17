#include <iostream>
#include <niu2x/unused.h>
#include <niu2x/type.h>
#include <niu2x/gfx.h>
#include <niu2x/fs.h>
#include <niu2x/stream.h>
#include <execinfo.h>
#include <cxxabi.h>

static void print_backtrace()
{
    const size_t max_backtrace_depth = 100;
    void* array[max_backtrace_depth];
    size_t stack_depth = backtrace(array, max_backtrace_depth);

    char** stack_trace = backtrace_symbols(array, stack_depth);
    if (stack_trace == nullptr) {
        std::cerr << "Error: backtrace_symbols returned nullptr\n";
        return;
    }

    for (size_t i = 0; i < stack_depth; ++i) {
        std::cout << stack_trace[i] << '\n';
    }

    free(stack_trace); // remember to free the result from backtrace_symbols
}

using namespace niu2x;

class PoeWinDelegate : public gfx::Window::Delegate {
public:
    PoeWinDelegate() { }
    ~PoeWinDelegate() { }

    void load_resource()
    {
        auto res_mgr = gfx::ResourceManager::get();

        res_mgr->load_render_program(gfx::RenderProgramID::TEXTURE_COLOR);
        res_mgr->load_render_program(gfx::RenderProgramID::COLOR);
        res_mgr->load_render_program(gfx::RenderProgramID::TEXT);

        res_mgr->load_image_sheet("resource/image/ui-pack.sheet");
        res_mgr->load_font("resource/font/normal.font");
        res_mgr->load_ui("resource/gui/main.ui");

        // auto font = res_mgr->get_font("font/normal");
        // font->prepare("Hello");
    }

    void setup() override
    {
        printf("setup\n");

        load_resource();

        auto res_mgr = gfx::ResourceManager::get();
        gui_root_ = res_mgr->build_ui("resource/gui/main.ui");
    }

    void cleanup() override
    {
        auto res_mgr = gfx::ResourceManager::get();
        res_mgr->clear();
        printf("cleanup\n");
    }

    void update(TimeDuration delta) override
    {
        static gfx::render_command::Clear clear;
        gfx::RenderCommandQueue::get()->enqueue(&clear);
        gui_root_->draw();
        gfx::render();
    }

    void on_resize(gfx::IntSize window_size) override
    {
        gfx::gui::update_view_projection(window_size);
        gui_root_->layout(window_size.width, window_size.height);
    }

    void on_key(gfx::KeyCode key_code) override
    {
        if (key_code == gfx::KeyCode::KEY_ESCAPE) {
            gfx::main_window()->close();
        }
    }

private:
    UniquePtr<gfx::gui::Node> gui_root_;
};

int main()
{
    try {
        auto window = gfx::WindowFactory::get()->create_window();
        auto poe_win_delegate = make_unique<PoeWinDelegate>();
        window->set_delegate(move(poe_win_delegate));
        // window->set_full_screen(true);
        window->poll();
    } catch (Exception& e) {
        std::cout << e.what() << std::endl;
        print_backtrace();
    }
    return 0;
}