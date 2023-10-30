#include <iostream>
#include <niu2x/unused.h>
#include <niu2x/type.h>
#include <niu2x/gfx.h>

using namespace niu2x;

class PoeWinDelegate : public gfx::Window::Delegate {
public:
    PoeWinDelegate() { }
    ~PoeWinDelegate() { }

    void setup() override
    {
        printf("setup\n");
        auto gfx_factory = gfx::GFX_Factory::get();

        render_program_
            = gfx_factory->create_render_program(gfx::RenderProgramID::COLOR);

        gfx::Vertex triangle[] = {
            { 0, 0, 0, 1, 0, 0, 1, 0, 0 },
            { 1, 0, 0, 1, 0, 0, 1, 0, 0 },
            { 1, 1, 0, 1, 0, 0, 1, 0, 0 },
        };

        vertex_buffer_ = gfx_factory->create_vertex_buffer();
        vertex_buffer_->resize(3);
        vertex_buffer_->set_vertexs(0, 3, triangle);
    }

    void cleanup() override
    {
        render_program_.reset();
        vertex_buffer_.reset();
    }

    void update(TimeDuration delta) override
    {
        gfx::Draw::clear();
        vertex_buffer_->bind();
        render_program_->bind();
        gfx::Draw::draw_triangles(0, 3);
    }

private:
    UniquePtr<gfx::RenderProgram> render_program_;
    UniquePtr<gfx::VertexBuffer> vertex_buffer_;
};

int main()
{
    try {
        auto poe_win_delegate = make_unique<PoeWinDelegate>();
        auto window = gfx::WindowFactory::get()->create_window();
        window->set_delegate(move(poe_win_delegate));
        window->poll();
    } catch (Exception& e) {
        std::cout << e.what() << std::endl;
    }
    return 0;
}