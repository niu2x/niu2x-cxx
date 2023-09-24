#include "ray_trace.h"

namespace niu2x::painter {

using math::Interval;
using math::to_color;

RayTracePainter::RayTracePainter()
: camera_({ 4, 3 }, 4)
{
    for (int i = 0; i < 10; i++) {
        hittable_objects_.insert(make_shared<Sphere>(Vec3(i, 8, 4), 0.5));
        hittable_objects_.insert(make_shared<Sphere>(Vec3(i, 8, 1), 0.5));
        hittable_objects_.insert(make_shared<Sphere>(Vec3(i, 8, 2), 0.5));
    }

    hittable_objects_.insert(make_shared<Sphere>(Vec3(0, 8, -40), 40));

    camera_.look_at(Vec3(0, 0, 0), Vec3(0, 1, -0.2), Vec3(0, 0, 1));
}

RayTracePainter::~RayTracePainter() { }

Color RayTracePainter::ray_color(const Ray& ray)
{
    auto hit = hittable_objects_.hit(ray, math::Interval(0.1, math::infinity));
    if (hit) {
        auto normal = hit.value().normal;
        return to_color(0.5 * (normal + Vec3(1, 1, 1)));
    }
    auto a = 0.5 * (ray.direction().z + 1.0);
    return to_color(Vec3(1.0, 1.0, 1.0) * (1.0 - a) + Vec3(0.5, 0.7, 1.0) * a);
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
