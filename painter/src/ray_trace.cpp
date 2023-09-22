#include "ray_trace.h"

namespace niu2x::painter {

const RayTracePainter::Camera default_camera = {
    { 2, 2 },
    {
        0,
        0,
        0,
    },
    {
        1,
        0,
        0,
    },
    {
        0,
        0,
        1,
    },
    2,
};

RayTracePainter::RayTracePainter()
: camera_(default_camera)
{
}

RayTracePainter::~RayTracePainter() { }
void RayTracePainter::paint(Image* image)
{
    auto ray_origin = camera_.pos;
    auto screen_center = ray_origin + camera_.look * camera_.focal_length;

    auto image_size = image->size();

    for (int row = 0; row < image_size.height; row++) {
        for (int col = 0; col < image_size.width; col++) {
            Vec3 pixel_pos = { (col + 0.5) / image_size.width - 0.5,
                (row + 0.5) / image_size.height - 0.5, 0 };
            pixel_pos += screen_center;
            auto ray_dir = normalize(pixel_pos - ray_origin);
            auto ray = Ray(ray_origin, ray_dir);
        }
    }
}

} // namespace niu2x::painter
