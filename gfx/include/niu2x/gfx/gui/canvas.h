#ifndef NIU2X_GFX_GUI_CANVAS_H
#define NIU2X_GFX_GUI_CANVAS_H

#include <niu2x/noncopyable.h>
#include <niu2x/gfx/hardward_resource.h>
#include <niu2x/gfx/image_sheet.h>
#include <niu2x/gfx/render_command.h>

namespace niu2x::gfx::gui {

using Rect = math::Rect<float>;

class Canvas : private Noncopyable {
public:
    Canvas();
    ~Canvas();
    void draw();
    void add_image(ImageSheet::Frame* frame, const Rect&);
    void clear();

private:
    struct ImageCommand {
        Rect rect;
        UniquePtr<VertexBuffer> vbo;
        UniquePtr<IndexBuffer> veo;
        UniformPacket uniforms;
        RenderProgram* program = nullptr;
        ImageSheet::Frame* frame = nullptr;
        render_command::Triangles draw;
        ImageCommand(const Rect&, ImageSheet::Frame*);
    };

    // using Command = Variant<ImageCommand>;
    Vector<ImageCommand> commands_;
};

} // namespace niu2x::gfx::gui

#endif