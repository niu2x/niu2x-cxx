#include "ray_trace.h"

namespace niu2x::painter {

// const RayTracePainter::Camera default_camera = {
//     { 4, 3 },
//     {
//         0,
//         0,
//         8,
//     },
//     {
//         0,
//         1,
//         0,
//     },
//     {
//         0,
//         0,
//         1,
//     },
//     2,
// };

RayTracePainter::RayTracePainter()
: camera_({ 4, 3 }, 4)
{
    for (int i = 0; i < 10; i++) {
        hittable_objects_.insert(make_shared<Sphere>(Vec3(i, 8, 6), 0.5));
        hittable_objects_.insert(make_shared<Sphere>(Vec3(i, 8, 7), 0.5));
        hittable_objects_.insert(make_shared<Sphere>(Vec3(i, 8, 8), 0.5));
        hittable_objects_.insert(make_shared<Sphere>(Vec3(i, 8, 9), 0.5));
    }

    camera_.look_at(Vec3(0, 0, 8), Vec3(0, 1, 0), Vec3(0, 0, 1));
}

RayTracePainter::~RayTracePainter() { }

Color RayTracePainter::ray_color(const Ray& ray)
{
    Vec3 light = normalize(Vec3(1, -1, 1));
    auto hit = hittable_objects_.hit(ray, 0.1, 100);
    if (hit) {
        auto normal = hit.value().normal;
        return ColorF(1, 1, 1) * max(dot(light, normal), 0.0);
    }
    auto a = 0.5 * (ray.direction().z + 1.0);
    return ColorF(1.0, 1.0, 1.0) * (1.0 - a) + ColorF(0.5, 0.7, 1.0) * a;
}

void RayTracePainter::paint(Image* image)
{
    auto ray_origin = camera_.pos;
    auto screen_center = ray_origin + camera_.look * camera_.focal_length;
    auto image_size = image->size();

    for (int row = 0; row < image_size.height; row++) {
        for (int col = 0; col < image_size.width; col++) {
            double px = (col + 0.5) / image_size.width - 0.5;
            double py = 0.5 - (row + 0.5) / image_size.height;
            px *= camera_.size.width;
            py *= camera_.size.height;
            auto pixel_pos
                = screen_center + px * camera_.side + py * camera_.up;
            auto ray_dir = normalize(pixel_pos - ray_origin);
            auto ray = math::Ray(ray_origin, ray_dir);
            image->set_pixel(row, col, ray_color(ray));
        }
    }
}

} // namespace niu2x::painter
