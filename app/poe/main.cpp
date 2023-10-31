#include <iostream>
#include <niu2x/unused.h>
#include <niu2x/type.h>
#include <niu2x/gfx.h>
#include <niu2x/fs.h>
#include <niu2x/stream.h>

using namespace niu2x;

class PoeWinDelegate : public gfx::Window::Delegate {
public:
    PoeWinDelegate() { }
    ~PoeWinDelegate() { }

    void setup() override
    {
        printf("setup\n");
        auto gfx_factory = gfx::GFX_Factory::get();

        render_program_ = gfx_factory->create_render_program(
            gfx::RenderProgramID::TEXTURE_COLOR);

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

        tex_ = gfx_factory->create_texture2d();

        fs::File png_file("test_00.png");
        stream::FileReadStream png_in(png_file);
        tex_->load(&png_in, gfx::PixelFormat::RGB_888);
    }

    void cleanup() override { printf("cleanup\n"); }

    void update(TimeDuration delta) override
    {
        gfx::Draw::clear();
        vertex_buffer_->bind();
        tex_->bind(0);
        render_program_->bind();
        render_program_->set_uniform_integer(
            gfx::RenderProgram::Uniform::TEX_0, 0);
        gfx::Draw::draw_triangles(0, 6);
    }

private:
    UniquePtr<gfx::RenderProgram> render_program_;
    UniquePtr<gfx::VertexBuffer> vertex_buffer_;
    UniquePtr<gfx::Texture2D> tex_;
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
    }
    return 0;
}