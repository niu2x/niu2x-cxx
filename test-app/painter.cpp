#include <niu2x/painter.h>
#include <niu2x/fs.h>
#include <niu2x/stream.h>
#include <niu2x/image.h>

using namespace niu2x;

int main()
{
    image::Image canvas;
    canvas.reset(512, 512, Color::WHITE);

    auto painter = painter::Painter::create(painter::PainterType::RAY_TRACE);
    painter->paint(&canvas);

    fs::File canvas_file("test.png");
    stream::FileWriteStream canvas_file_writer(canvas_file);
    canvas.store_to(&canvas_file_writer);

    return 0;
}