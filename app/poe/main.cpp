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

    void setup() override
    {
        printf("setup\n");
        auto gfx_factory = gfx::GFX_Factory::get();
        auto res_mgr = gfx::ResourceManager::get();

        res_mgr->load_render_program(gfx::RenderProgramID::TEXTURE_COLOR);
        res_mgr->load_render_program(gfx::RenderProgramID::COLOR);

        render_program_
            = res_mgr->get_render_program(gfx::RenderProgramID::TEXTURE_COLOR);

        gfx::Vertex triangle[] = {
            { 0, 0, 0, 1, 1, 1, 1, 0, 0 },
            { 1, 0, 0, 1, 1, 1, 1, 1, 0 },
            { 1, 1, 0, 1, 1, 1, 1, 1, 1 },

            { 0, 0, 0, 1, 1, 1, 1, 0, 0 },
            { 1, 1, 0, 1, 1, 1, 1, 1, 1 },
            { 0, 1, 0, 1, 1, 1, 1, 0, 1 },

        };

        vertex_buffer_ = gfx_factory->create_vertex_buffer();
        vertex_buffer_->resize(6);
        vertex_buffer_->set_vertexs(0, 6, triangle);

        res_mgr->load_texture2d("resource/image/test_00.yml");
        tex_ = res_mgr->get_texture2d("resource/image/test_00.yml");

        res_mgr->load_vertex_buffer("resource/vertex_buffer/square.yml");

        gui_root_ = make_unique<gfx::gui::Node>();
    }

    void cleanup() override
    {
        auto res_mgr = gfx::ResourceManager::get();
        res_mgr->clear();
        printf("cleanup\n");
    }

    void update(TimeDuration delta) override
    {
        gfx::RenderCommandQueue::get()->enqueue(
            gfx::RenderCommandFactory::get()->create_clear());
        gui_root_->draw();
        gfx::render();

        // gfx::Draw::clear();
        // vertex_buffer_->bind();
        // tex_->bind(0);
        // render_program_->bind();
        // render_program_->set_uniform_integer(
        //     gfx::RenderProgram::Uniform::TEX_0, 0);

        // gfx::Mat4 unit_mat4 { { 1, 0, 0, 0 }, { 0, 1, 0, 0 }, { 0, 0, 1, 0 },
        //     { 0, 0, 0, 1 } };

        // render_program_->set_uniform_mat4(
        //     gfx::RenderProgram::Uniform::MODEL, unit_mat4);

        // render_program_->set_uniform_mat4(
        //     gfx::RenderProgram::Uniform::VIEW, unit_mat4);

        // render_program_->set_uniform_mat4(
        //     gfx::RenderProgram::Uniform::PROJECTION, unit_mat4);

        // gfx::Draw::draw_triangles(0, 6);
    }

private:
    gfx::RenderProgram* render_program_;
    UniquePtr<gfx::VertexBuffer> vertex_buffer_;
    gfx::Texture2D* tex_;
    UniquePtr<gfx::gui::Node> gui_root_;
};

int main()
{
    try {
        auto window = gfx::WindowFactory::get()->create_window();
        auto poe_win_delegate = make_unique<PoeWinDelegate>();
        window->set_delegate(move(poe_win_delegate));
        window->poll();
    } catch (Exception& e) {
        std::cout << e.what() << std::endl;
        print_backtrace();
    }
    return 0;
}